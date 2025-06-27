#include "time_utils.h"

#include "../secrets.h"



TimeUtils::TimeUtils() : lastSyncEpoch(0), lastSyncMillis(0), lastNTPSyncMillis(0) {}

int TimeUtils::getDSTOffset() { return DAYLIGHT_SAVING_TIME ? 3600 : 0; }

int TimeUtils::getTimeZoneOffset() { return TIMEZONE_OFFSET * 3600; }

// Removed erroneous update() function; if you intended to override a virtual method, declare it properly in the class header and implement as TimeUtils::update() here.
void TimeUtils::update() {
     // Implement your update logic here, if needed.
     // For example, you could periodically check if a resync is needed.
     syncWithNTP(); // This will trigger NTP sync if needed.
}
bool TimeUtils::syncWithNTP()
{
     configTime(getTimeZoneOffset(), getDSTOffset(),
          ntpServer);  // NTP sync, no offsets here

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
          lastSyncEpoch = time(nullptr);
          lastSyncMillis = millis();
          lastNTPSyncMillis = lastSyncMillis;

          char timeStr[64];
          strftime(timeStr, sizeof(timeStr), "%A, %B %d %Y %H:%M:%S %Z",
               &timeinfo);  // %Z for timezone
          // abbrev
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

void TimeUtils::init() { syncWithNTP(); }

const char* TimeUtils::getFormattedTime() 
{
     static char timeStr[20];

     unsigned long nowMillis = millis();

     if (nowMillis - lastNTPSyncMillis >= SYNC_INTERVAL)
     {
          syncWithNTP();
          nowMillis = millis();  // update after resync
     }

     time_t now = lastSyncEpoch + (nowMillis - lastSyncMillis) / 1000;
     struct tm* timeinfo = localtime(&now);  // converts UTC epoch to local time

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
