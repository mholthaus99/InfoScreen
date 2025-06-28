#include "rss_reader.h"

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include "../secrets.h"

namespace RSS {
static constexpr size_t MAX_HEADLINES = 10;
static constexpr size_t MAX_TITLE_LEN = 100;

static char cachedHeadlines[MAX_HEADLINES][MAX_TITLE_LEN];
static size_t headlineCount = 0;
static size_t currentHeadlineIndex = 0;
static unsigned long lastRSSUpdate = 0;

const char* url = NEWS_URL;

static void clearHeadlines() {
    Serial.println("[RSS] Clearing headlines...");
    headlineCount = 0;
    currentHeadlineIndex = 0;
    for (size_t i = 0; i < MAX_HEADLINES; i++) {
        cachedHeadlines[i][0] = '\0';
    }
}

void fetch() {
    Serial.printf("[RSS] Free heap before fetch: %lu bytes\n", ESP.getFreeHeap());

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[RSS] WiFi not connected. Skipping fetch.");
        return;
    }

    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    http.addHeader("User-Agent", "ESP8266 JSON RSS Reader");
    http.addHeader("Accept-Encoding", "identity");

    Serial.printf("[RSS] Fetching headlines from: %s\n", url);

    if (!http.begin(client, url)) {
        Serial.println("[RSS] Failed to begin HTTP request.");
        return;
    }

    int httpCode = http.GET();
    yield();  // <-- Yield after blocking network call

    if (httpCode != HTTP_CODE_OK) {
        Serial.printf("[RSS] HTTP error code: %d\n", httpCode);
        http.end();
        return;
    }

    String payload = http.getString();
    http.end();
    yield();  // <-- Yield after reading HTTP response

    DynamicJsonDocument* doc = new DynamicJsonDocument(2048);
    DeserializationError error = deserializeJson(*doc, payload);
    yield();  // <-- Yield after JSON parsing

    if (error) {
        Serial.printf("[RSS] JSON deserialization failed: %s\n", error.c_str());
        delete doc;
        return;
    }

    if (!doc->is<JsonArray>()) {
        Serial.println("[RSS] JSON payload is not an array.");
        delete doc;
        return;
    }

    JsonArray arr = doc->as<JsonArray>();
    size_t count = 0;

    for (const auto& item : arr) {
        if (!item.is<const char*>()) continue;
        const char* title = item.as<const char*>();
        if (!title || title[0] == '\0') continue;
        count++;
        if (count >= MAX_HEADLINES) break;
        yield();  // <-- Yield inside loop to avoid watchdog reset
    }

    if (count == 0) {
        Serial.println("[RSS] No valid headlines found.");
        delete doc;
        return;
    }

    clearHeadlines();

    size_t index = 0;
    for (const auto& item : arr) {
        if (!item.is<const char*>()) continue;
        const char* title = item.as<const char*>();
        if (!title || title[0] == '\0') continue;

        strncpy(cachedHeadlines[index], title, MAX_TITLE_LEN - 1);
        cachedHeadlines[index][MAX_TITLE_LEN - 1] = '\0';

        Serial.printf("[RSS] Cached headline %d: %s\n", index, cachedHeadlines[index]);
        index++;
        if (index >= MAX_HEADLINES) break;
        yield();  // <-- Yield here as well
    }

    headlineCount = index;
    lastRSSUpdate = millis();

    delete doc;

    Serial.printf("[RSS] Successfully cached %d headlines\n", headlineCount);
    Serial.printf("[RSS] Free heap after fetch: %lu bytes\n", ESP.getFreeHeap());
}

const char* getNextHeadline() {
    Serial.println("[RSS] getNextHeadline() called");

    unsigned long now = millis();

    // Only fetch if the cache is empty or expired
    if ((headlineCount == 0) || (now - lastRSSUpdate >= 15UL * 60UL * 1000UL)) {
        Serial.println("[RSS] Cache empty or expired. Fetching...");
        size_t previousCount = headlineCount;
        fetch();

        // If fetch failed, don't wipe old cache
        if (headlineCount == 0 && previousCount > 0) {
            Serial.println("[RSS] Fetch failed, keeping old cache.");
            headlineCount = previousCount;
        }
    }

    if (headlineCount == 0) {
        Serial.println("[RSS] No headlines available.");
        return "No headlines available";
    }

    const char* headline = cachedHeadlines[currentHeadlineIndex];
    Serial.printf("[RSS] Returning headline %d: %s\n", currentHeadlineIndex, headline);

    currentHeadlineIndex = (currentHeadlineIndex + 1) % headlineCount;

    if (!headline || headline[0] == '\0') {
        Serial.println("[RSS] Invalid or empty headline.");
        return "No headlines available";
    }

    return headline;
}

}  // namespace RSS
