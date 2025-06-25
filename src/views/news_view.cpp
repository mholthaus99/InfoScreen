#include "news_view.h"
#include "../network/rss_reader.h"
#include "../system/display.h"
#include "../system/view_controller.h"

namespace Views
{

    void NewsView::render()
    {
        if (millis() - timeOfLastTitleChange >= 5000)
        {
            const char *headline = RSS::getNextHeadline();

            if (headline && headline[0] != '\0')
            {
                LCD::printWrapped(headline);
            }
            else
            {
                LCD::printAt("No headlines", 1);
            }

            timeOfLastTitleChange = millis();
        }
    }

    void NewsView::onSkip()
    {
        const char *headline = RSS::getNextHeadline();

        if (headline && headline[0] != '\0')
        {
            LCD::printWrapped(headline);
        }
        else
        {
            LCD::printAt("No headlines", 1);
        }
    }

} // namespace Views
