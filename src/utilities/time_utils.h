#pragma once
#include <Arduino.h>
#include <time.h>

#include "../interfaces/IObject.h"
#include "../interfaces/ITime.h"
#include "../secrets.h"

class TimeUtils : public ITime, public IObject {
   public:
    // TimeUtils(const char* ntpServer = "time.nist.gov", long timezoneOffset = 0,
    // bool daylightSavingTime = false);
    TimeUtils();
    void init() override;
    const char* getFormattedTime() override;
    void update() override;

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
