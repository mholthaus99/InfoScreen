/**
 * @file time_utils.cpp
 * @brief Time synchronization and formatting utilities using NTP.
 */

#include "time_utils.h"
#include <time.h>

// === NTP Configuration ===

/**
 * @brief NTP server used for time synchronization.
 */
const char *ntpServer = "time.nist.gov";

/**
 * @brief GMT offset in seconds (Central Standard Time).
 */
const long gmtOffset_sec = -6 * 3600;

/**
 * @brief Daylight Saving Time offset in seconds.
 */
const int daylightOffset_sec = 3600;

// === Internal time tracking ===

/**
 * @brief Base Unix time set during the last successful NTP sync.
 */
static time_t baseTime = 0;

/**
 * @brief Millis at the time of the last successful NTP sync.
 */
static unsigned long baseMillis = 0;

/**
 * @brief Millis timestamp of the last synchronization.
 */
static unsigned long lastSyncMillis = 0;

/**
 * @brief Interval (in ms) to sync time from NTP server (10 minutes).
 */
const unsigned long SYNC_INTERVAL = 10UL * 60UL * 1000UL;

/**
 * @brief Synchronizes system time using NTP.
 * 
 * This function configures time using a specified NTP server,
 * waits for a valid time response (with retries), and updates internal time tracking variables.
 * 
 * @return true if synchronization was successful, false otherwise.
 */
bool time_fetchNTP()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  struct tm timeinfo;
  int retry = 0;
  const int retry_count = 10;

  while (!getLocalTime(&timeinfo) && retry < retry_count)
  {
    Serial.println("Waiting for NTP time sync...");
    delay(1000);
    retry++;
  }

  if (retry < retry_count)
  {
    baseTime = mktime(&timeinfo);
    baseMillis = millis();
    lastSyncMillis = baseMillis;

    char timeStr[64];
    strftime(timeStr, sizeof(timeStr), "%A, %B %d %Y %H:%M:%S", &timeinfo);
    Serial.println("Time synchronized:");
    Serial.println(timeStr);
    return true;
  }
  else
  {
    Serial.println("Failed to sync time.");
    return false;
  }
}

/**
 * @brief Sets up the time system by performing an initial NTP synchronization.
 */
void time_init()
{
  time_fetchNTP();
}

/**
 * @brief Returns the current formatted time as a C-style string.
 * 
 * Automatically checks if an NTP resync is needed based on the sync interval.
 * The time is computed by adding the elapsed time (in seconds) since the last sync to the base time.
 * 
 * @return A pointer to a static C-style string in the format "HH:MM:SS AM/PM", or "Time error".
 */
const char* time_getprint()
{
  static char timeStr[20]; // static so it's retained between calls
  unsigned long nowMillis = millis();

  // Auto-sync if enough time has passed
  if (nowMillis - lastSyncMillis >= SYNC_INTERVAL)
  {
    time_fetchNTP();
    nowMillis = millis(); // update after sync
  }

  time_t now = baseTime + (nowMillis - baseMillis) / 1000;
  struct tm* timeinfo = localtime(&now);

  if (timeinfo)
  {
    strftime(timeStr, sizeof(timeStr), "%I:%M:%S %p", timeinfo);
    return timeStr;
  }
  else
  {
    return "Time error";
  }
}


