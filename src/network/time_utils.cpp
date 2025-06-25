/**
 * @file time_utils.cpp
 * @brief Provides utilities for time synchronization and formatting using NTP.
 *
 * This module handles NTP time synchronization, tracks internal system time,
 * and provides formatted time strings for display. It automatically resynchronizes
 * with the NTP server at a defined interval and accounts for daylight saving time.
 *
 * Functions:
 * - init(): Initializes time synchronization with the NTP server.
 * - getFormattedTime(): Returns the current time as a formatted string (HH:MM:SS AM/PM).
 *
 * Internal Functions:
 * - fetchNTP(): Synchronizes system time using NTP and updates internal time tracking.
 * - getDaylightOffset_sec(): Returns the daylight saving time offset in seconds.
 *
 * Constants:
 * - ntpServer: The NTP server address used for synchronization.
 * - SYNC_INTERVAL: Interval in milliseconds between automatic NTP synchronizations.
 *
 * Internal State:
 * - baseTime: The last synchronized epoch time.
 * - baseMillis: The millis() value at the last synchronization.
 * - lastSyncMillis: The millis() value at the last NTP sync.
 */

#include "time_utils.h"
#include <time.h>
#include "secrets.h"

namespace TimeUtils
{

  // === NTP Configuration ===
  const char *ntpServer = "time.nist.gov";

  /**
   * @brief Last synchronized epoch time (seconds since Jan 1, 1970 UTC).
   */
  static time_t baseTime = 0;

  /**
   * @brief Value of millis() at the last successful NTP synchronization.
   */
  static unsigned long baseMillis = 0;

  /**
   * @brief Value of millis() at the last NTP synchronization attempt.
   */
  static unsigned long lastSyncMillis = 0;

  /**
   * @brief Interval in milliseconds between automatic NTP synchronizations.
   */
  const unsigned long SYNC_INTERVAL = 10UL * 60UL * 1000UL; // 10 minutes

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

  void init()
  {
    fetchNTP();
  }

  const char *getFormattedTime()
  {
    static char timeStr[20]; // static buffer

    unsigned long nowMillis = millis();

    // Auto-resync if needed
    if (nowMillis - lastSyncMillis >= SYNC_INTERVAL)
    {
      fetchNTP();
      nowMillis = millis(); // update after resync
    }

    time_t now = baseTime + (nowMillis - baseMillis) / 1000;
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
