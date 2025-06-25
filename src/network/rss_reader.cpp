/**
 * @file rss_reader.cpp
 * @brief Implements RSS headline fetching and caching for ESP8266.
 *
 * This module provides functionality to fetch RSS headlines from a remote server,
 * cache them locally, and provide access to the headlines in a rotating manner.
 * Headlines are fetched as a JSON array of strings from a URL defined in `NEWS_URL`.
 * 
 * Features:
 * - Fetches up to MAX_HEADLINES headlines from a remote JSON RSS endpoint.
 * - Caches headlines in memory for efficient access.
 * - Automatically refreshes headlines every 15 minutes or when cache is empty.
 * - Provides a function to retrieve the next headline in a rotating fashion.
 * 
 * Dependencies:
 * - ESP8266WiFi.h
 * - WiFiClientSecure.h
 * - ESP8266HTTPClient.h
 * - ArduinoJson.h
 * - secrets.h (for NEWS_URL)
 * 
 * Namespace: RSS
 * 
 * Functions:
 * - void fetch(): Fetches and caches headlines from the RSS endpoint.
 * - const char* getNextHeadline(): Returns the next headline, refreshing cache if needed.
 */

#include "rss_reader.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "../secrets.h"

namespace RSS
{

    static constexpr size_t MAX_HEADLINES = 10;
    static constexpr size_t MAX_TITLE_LEN = 100;

    static char cachedHeadlines[MAX_HEADLINES][MAX_TITLE_LEN];
    static size_t headlineCount = 0;
    static size_t currentHeadlineIndex = 0;
    static unsigned long lastRSSUpdate = 0;

    const char *url = NEWS_URL;

     

    static void clearHeadlines()
    {
        headlineCount = 0;
        currentHeadlineIndex = 0;
        for (size_t i = 0; i < MAX_HEADLINES; i++)
            cachedHeadlines[i][0] = '\0';
    }

    void fetch()
    {
        clearHeadlines();

        if (WiFi.status() != WL_CONNECTED)
            return;

        WiFiClientSecure client;
        client.setInsecure();

        HTTPClient http;
        http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
        http.addHeader("User-Agent", "ESP8266 JSON RSS Reader");
        http.addHeader("Accept-Encoding", "identity");

        if (!http.begin(client, url))
            return;

        int httpCode = http.GET();
        if (httpCode != HTTP_CODE_OK)
        {
            http.end();
            return;
        }

        String payload = http.getString();
        http.end();

        DynamicJsonDocument doc(2048);
        if (deserializeJson(doc, payload))
            return;
        if (!doc.is<JsonArray>())
            return;

        JsonArray arr = doc.as<JsonArray>();
        size_t count = 0;
        for (const auto &item : arr)
        {
            if (!item.is<const char *>())
                continue;
            if (count >= MAX_HEADLINES)
                break;

            const char *title = item.as<const char *>();
            strncpy(cachedHeadlines[count], title, MAX_TITLE_LEN - 1);
            cachedHeadlines[count][MAX_TITLE_LEN - 1] = '\0';
            count++;
        }

        headlineCount = count;
        lastRSSUpdate = millis();
    }

    const char *getNextHeadline()
    {
        unsigned long now = millis();
        if (now - lastRSSUpdate >= 15UL * 60UL * 1000UL || headlineCount == 0)
            fetch();

        if (headlineCount == 0)
            return "No headlines available";

        const char *headline = cachedHeadlines[currentHeadlineIndex];
        currentHeadlineIndex = (currentHeadlineIndex + 1) % headlineCount;
        return headline;
    }

} // namespace RSS
