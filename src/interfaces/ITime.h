#pragma once

class ITime {
public:

     virtual const char* getFormattedTime() = 0;
     virtual void update() = 0;
     virtual ~ITime() {}
};
     