#pragma once
class IWeather {
   public:
    virtual const char* getCurrentConditions() = 0;
    virtual const char* getLocation() = 0;
    virtual const char* getTemperature() = 0;

    virtual ~IWeather() {}
};
