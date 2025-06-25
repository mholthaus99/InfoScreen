#include "mode_manager.h"

#include "../views/view.h"
#include "../views/default_view.h"
#include "../views/news_view.h"
#include "../views/menu_view.h"


using namespace Views;

namespace ModeManager {

    static View* currentView = nullptr;
    static DisplayMode currentMode = MODE_DEFAULT;

    void switchView(DisplayMode mode)
    {
        if (currentView)
        {
            currentView->onExit();
            delete currentView;
            currentView = nullptr;
        }

        currentMode = mode;

        switch (mode)
        {
        case MODE_DEFAULT:
            currentView = new DefaultView();
            break;
        case MODE_MENU:
        {
            auto* menu = new FunctionView();
            menu->setSwitchViewCallback(ModeManager::setMode);  // Allows menu to change mode
            currentView = menu;
            break;
        }
        case MODE_NEWS:
            currentView = new NewsView();
            break;
        case MODE_NETWORK:
            // TODO: Replace with NetworkView once implemented
            currentView = new DefaultView();
            break;
        default:
            currentView = new DefaultView();
            break;
        }

        if (currentView)
            currentView->onEnter();
    }

    void renderCurrentView()
    {
        if (currentView)
            currentView->render();
    }

    void setMode(DisplayMode mode)
    {
        switchView(mode);
    }

    DisplayMode getMode()
    {
        return currentMode;
    }

    View* getCurrentView(){
      return currentView;
    }
}
