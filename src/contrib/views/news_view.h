#pragma once
#include <Arduino.h>

#include "../../interfaces/IView.h"
#include "../helpers/rss_reader.h"

class NewsView : public View {
   private:
    /**
     * @brief Time of the last headline change in milliseconds.
     */
    unsigned long timeOfLastTitleChange = 0;

    /**
     * @brief Draws the next headline on the display.
     */
    void drawNextHeadline();

   public:
    /**
     * @brief Overridden: Renders the news headline and updates every 5 seconds.
     */
    void render() override;

    /**
     * @brief Overridden: Handles IR "skip" event by advancing to next headline.
     */
    void onSkip() override;
};
