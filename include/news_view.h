#pragma once

#include "view.h"
#include "weather.h"    // For getprint_weather_summary()
#include "time_utils.h" // For time_getprint()
#include "display.h"
#include "rss_reader.h"
#include "mode_manager.h" // For MODE_NEWS

class NewsView : public View
{
private:
    unsigned long timeOfLastTitleChange = 0; // Timestamp of the last change to the title on the news display
public:
    void render() override
    {
        if (displayMgr.shouldUpdate(MODE_NEWS))
        {
            printWrapped(rss_getprint_headline()); // This will update the headline
            timeOfLastTitleChange = millis();
            displayMgr.markUpdated();
        }

        if (millis() - timeOfLastTitleChange >= 5000)
        {
            timeOfLastTitleChange = millis();

            printWrapped(rss_getprint_headline()); // This will update the headline
        }
    }

    void onSkip() override
    {
        // Logic specific to the news view when skip is pressed
        // For example, navigate to the next news item
        printWrapped(rss_getprint_headline()); // Assuming you have a function to get the next headline
        displayMgr.markUpdated();
    }

    void onBack() override
    {
        // Logic specific to the weather view when back is pressed
        // For example, navigate back to the default view
        // mode_manager.setMode(MODE_DEFAULT); // Assuming you have a way to change modes
    }

    // Other IR handlers specific to WeatherView, if any
};
