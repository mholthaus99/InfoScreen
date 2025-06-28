#include <Arduino.h>
#pragma once
/**
 * @brief Interface for news sources.
 *
 * This interface defines the required methods for any news source implementation.
 * Classes implementing this interface should provide mechanisms to retrieve news headlines,
 * the total number of available headlines, and update the news data.
 */
class INews {
   public:
    virtual const char* getHeadline(uint8_t index) = 0;
    virtual uint8_t getHeadlineCount() = 0;
    virtual void update() = 0;
    virtual ~INews() {}
};
