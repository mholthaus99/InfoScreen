#pragma once
#include "view.h"

namespace Views
{

    /**
     * @brief View for displaying news headlines with timed updates.
     */
    class NewsView : public View
    {
    private:
        unsigned long timeOfLastTitleChange = 0;

    public:
        /**
         * @brief Renders the news headline and updates every 5 seconds.
         */
        void render() override;

        /**
         * @brief Handles IR "skip" event by advancing to next headline.
         */
        void onSkip() override;

   
    };

} // namespace Views
