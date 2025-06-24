// rss_reader.cpp
#include "rss_reader.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

/**
 * @brief Maximum number of headlines to cache.
 */
static constexpr size_t MAX_HEADLINES = 10;

/**
 * @brief Maximum length of each headline string.
 */
static constexpr size_t MAX_TITLE_LEN = 100;

/**
 * @brief Cached headlines buffer.
 */
static char cachedHeadlines[MAX_HEADLINES][MAX_TITLE_LEN];

/**
 * @brief Number of headlines currently cached.
 */
static size_t headlineCount = 0;

/**
 * @brief Index of the current headline to display.
 */
static size_t currentHeadlineIndex = 0;

/**
 * @brief Timestamp of last successful RSS fetch (milliseconds since start).
 */
static unsigned long lastRSSUpdate = 0;

/**
 * @brief URL of the JSON RSS feed to fetch.
 */
const char *url = "https://maxholthaus.com/ssr";

/**
 * @brief Clears all cached headlines and resets counters.
 */
static void clearHeadlines()
{
    headlineCount = 0;
    currentHeadlineIndex = 0;
    for (size_t i = 0; i < MAX_HEADLINES; i++)
        cachedHeadlines[i][0] = '\0';
}

/**
 * @brief Fetches and parses RSS headlines from the JSON feed URL.
 * 
 * Clears any previously cached headlines before fetching.
 * Uses WiFiClientSecure with insecure mode (for testing).
 * Stores up to MAX_HEADLINES headlines in the cache.
 * Does nothing if Wi-Fi is not connected or fetch fails.
 */
void rss_fetch()
{
    clearHeadlines();

    if (WiFi.status() != WL_CONNECTED)
    {
        return;
    }

    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    http.addHeader("User-Agent", "ESP8266 JSON RSS Reader");
    http.addHeader("Accept-Encoding", "identity");

    if (!http.begin(client, url))
    {
        return;
    }

    int httpCode = http.GET();

    if (httpCode != HTTP_CODE_OK)
    {
        http.end();
        return;
    }

    String payload = http.getString();
    http.end();

    DynamicJsonDocument doc(2048);
    auto error = deserializeJson(doc, payload);
    if (error)
    {
        return;
    }

    if (!doc.is<JsonArray>())
    {
        return;
    }

    JsonArray arr = doc.as<JsonArray>();
    size_t count = 0;

    for (const auto &item : arr)
    {
        if (!item.is<const char *>()) continue;
        if (count >= MAX_HEADLINES) break;

        const char *title = item.as<const char *>();
        strncpy(cachedHeadlines[count], title, MAX_TITLE_LEN - 1);
        cachedHeadlines[count][MAX_TITLE_LEN - 1] = '\0';
        count++;
    }

    headlineCount = count;
    lastRSSUpdate = millis();
}

/**
 * @brief Returns the next cached headline.
 * 
 * Automatically refreshes the headlines by calling rss_fetch()
 * if more than 15 minutes have elapsed since last update
 * or if no headlines are cached.
 * 
 * @return const char* Pointer to the current headline string.
 *         Returns "No headlines available" if cache is empty.
 */
const char *rss_getprint_headline()
{
    unsigned long now = millis();

    if (now - lastRSSUpdate >= 15UL * 60UL * 1000UL || headlineCount == 0)
        rss_fetch();

    if (headlineCount == 0)
        return "No headlines available";

    const char *headline = cachedHeadlines[currentHeadlineIndex];
    currentHeadlineIndex = (currentHeadlineIndex + 1) % headlineCount;
    return headline;
}
