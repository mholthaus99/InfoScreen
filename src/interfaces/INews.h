#include <Arduino.h>

class INews {
public:
     virtual const char* getHeadline(uint8_t index) = 0;
     virtual uint8_t getHeadlineCount() = 0;
     virtual void update() = 0;
     virtual ~INews() {}
};
     