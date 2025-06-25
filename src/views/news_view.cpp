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
            LCD::printWrapped(RSS::getNextHeadline());
            timeOfLastTitleChange = millis();
            displayMgr.markUpdated();
        }

        if (millis() - timeOfLastTitleChange >= 5000)
        {
            timeOfLastTitleChange = millis();
            LCD::printWrapped(RSS::getNextHeadline());
        }
    }

    void NewsView::onSkip()
    {
        LCD::printWrapped(RSS::getNextHeadline());
        displayMgr.markUpdated();
    }

} // namespace Views
