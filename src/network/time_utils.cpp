/**
 * @file time_utils.cpp
 * @brief Provides utilities for time synchronization and formatting using NTP.
 *
 * This module handles NTP synchronization, tracks system uptime for accurate
 * timekeeping between syncs, and provides human-readable formatted time strings.
 *
 * Public Functions:
 * - void init(): Initializes NTP synchronization.
 * - const char* getFormattedTime(): Returns current time as a string (HH:MM:SS AM/PM).
 *
 * Internal Functions:
 * - bool syncWithNTP(): Synchronizes system time with the NTP server.
 * - int getDaylightOffset(): Returns daylight saving offset in seconds.
 *
 * Constants:
 * - const char* ntpServer: NTP server address.
 * - const unsigned long SYNC_INTERVAL: Interval between NTP synchronizations.
 *
 * Internal State:
 * - time_t lastSyncEpoch: Epoch time of last successful NTP sync.
 * - unsigned long lastSyncMillis: millis() value when last NTP sync occurred.
 * - unsigned long lastNTPUpdateMillis: Timestamp for next scheduled sync.
 */

#include "time_utils.h"
#include <time.h>
#include "secrets.h"

namespace TimeUtils
{

  // === NTP Configuration ===
  const char *NTP_SERVER = "time.nist.gov";

  /**
   * @brief Last synchronized epoch time (seconds since Jan 1, 1970 UTC).
   */
  static time_t lastSyncEpoch = 0;

  /**
   * @brief Value of millis() at the last successful NTP synchronization.
   */
  static unsigned long lastSync = 0;

  /**
   * @brief Value of millis() at the last NTP synchronization attempt.
   */
  static unsigned long lastNTPSync = 0;

  /**
   * @brief Interval in milliseconds between automatic NTP synchronizations.
   */
  const unsigned long SYNC_INTERVAL = 10UL * 60UL * 1000UL; // 10 minutes

  static int getDSTOffset()
  {
    return DAYLIGHT_SAVING_TIME ? 3600 : 0; // 1 hour if DST is enabled
  }

  /**
   * @brief Synchronizes system time using NTP.
   *
   * @return true if synchronization was successful, false otherwise.
   */
  static bool syncWithNTP()
  {
    configTime(TIMEZONE_OFFSET, getDSTOffset(), NTP_SERVER);

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
      lastSyncEpoch = mktime(&timeinfo);
      lastSync = millis();
      lastNTPSync = lastSync;

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

  void init()
  {
    syncWithNTP();
  }

  const char *getFormattedTime()
  {
    static char timeStr[20]; // static buffer

    unsigned long nowMillis = millis();

    // Auto-resync if needed
    if (nowMillis - lastNTPSync >= SYNC_INTERVAL)
    {
      syncWithNTP();
      nowMillis = millis(); // update after resync
    }

    time_t now = lastSyncEpoch + (nowMillis - lastSync) / 1000;
    struct tm *timeinfo = localtime(&now);

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

} // namespace TimeUtils
