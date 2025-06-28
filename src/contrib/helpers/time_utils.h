#pragma once
#include <Arduino.h>
#include <time.h>


#include "../../secrets.h"

class TimeUtils {
   public:
    TimeUtils();

    const char* getFormattedTime();  // override;

   private:
    bool syncWithNTP();
    int getDSTOffset();
    int getTimeZoneOffset();

    const char* ntpServer = "time.nist.gov";

    time_t lastSyncEpoch;
    unsigned long lastSyncMillis;
    unsigned long lastNTPSyncMillis;

    static constexpr unsigned long SYNC_INTERVAL = 10UL * 60UL * 1000UL;  // 10 minutes
};
