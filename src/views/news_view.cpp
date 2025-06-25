#include "news_view.h"
#include "../network/rss_reader.h"
#include "../system/display.h"
#include "../system/mode_manager.h"

namespace Views
{
    void NewsView::render()
    {
        if (displayMgr.shouldUpdate(MODE_NEWS))
        {
            LCD::printWrapped(rss_getprint_headline());
            timeOfLastTitleChange = millis();
            displayMgr.markUpdated();
        }

        if (millis() - timeOfLastTitleChange >= 5000)
        {
            timeOfLastTitleChange = millis();
            LCD::printWrapped(rss_getprint_headline());
        }
    }

    void NewsView::onSkip()
    {
        LCD::printWrapped(rss_getprint_headline());
        displayMgr.markUpdated();
    }

} // namespace Views
