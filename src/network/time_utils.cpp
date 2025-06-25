/**
 * @file time_utils.cpp
 * @brief Time synchronization and formatting utilities using NTP.
 */

#include "time_utils.h"
#include <time.h>
#include "secrets.h"

namespace TimeUtils {

// === NTP Configuration ===
const char* ntpServer = "time.nist.gov";
// const long gmtOffset_sec = -6 * 3600;     // CST
// const int daylightOffset_sec = 3600;      // DST offset

// === Internal time tracking ===
static time_t baseTime = 0;
static unsigned long baseMillis = 0;
static unsigned long lastSyncMillis = 0;
const unsigned long SYNC_INTERVAL = 10UL * 60UL * 1000UL;  // 10 minutes

static int getDaylightOffset_sec()
{
  return DAYLIGHT_SAVING_TIME ? 3600 : 0; // 1 hour if DST is enabled
}

/**
 * @brief Synchronizes system time using NTP.
 * 
 * @return true if synchronization was successful, false otherwise.
 */
static bool fetchNTP()
{
  configTime(TIMEZONE_OFFSET, getDaylightOffset_sec(), ntpServer);

  struct tm timeinfo;
  int retry = 0;
  const int retry_count = 10;

  while (!getLocalTime(&timeinfo) && retry < retry_count) {
    Serial.println("Waiting for NTP time sync...");
    delay(1000);
    retry++;
  }

  if (retry < retry_count) {
    baseTime = mktime(&timeinfo);
    baseMillis = millis();
    lastSyncMillis = baseMillis;

    char timeStr[64];
    strftime(timeStr, sizeof(timeStr), "%A, %B %d %Y %H:%M:%S", &timeinfo);
    Serial.println("Time synchronized:");
    Serial.println(timeStr);
    return true;
  } else {
    Serial.println("Failed to sync time.");
    return false;
  }
}

void init()
{
  fetchNTP();
}

const char* getFormattedTime()
{
  static char timeStr[20]; // static buffer

  unsigned long nowMillis = millis();

  // Auto-resync if needed
  if (nowMillis - lastSyncMillis >= SYNC_INTERVAL) {
    fetchNTP();
    nowMillis = millis(); // update after resync
  }

  time_t now = baseTime + (nowMillis - baseMillis) / 1000;
  struct tm* timeinfo = localtime(&now);

  if (timeinfo) {
    strftime(timeStr, sizeof(timeStr), "%I:%M:%S %p", timeinfo);
    return timeStr;
  } else {
    return "Time error";
  }
}

}  // namespace TimeUtils
