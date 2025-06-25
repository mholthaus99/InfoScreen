#include "mode_manager.h"

#include "../views/view.h"
#include "../views/default_view.h"
#include "../views/news_view.h"
#include "../views/menu_view.h"

using namespace Views;

namespace ModeManager
{

  static View *currentView = nullptr;
  static DisplayMode currentMode = MODE_DEFAULT;

  void switchView(DisplayMode mode)
  {
    LCD::clear();
    View *oldView = currentView; // Hold old pointer but don't delete yet

    // Create new view pointer, but don't assign to currentView yet
    View *newView = nullptr;

    currentMode = mode;

    switch (mode)
    {
    case MODE_DEFAULT:
      newView = new DefaultView();
      break;
    case MODE_MENU:
    {
      auto *menu = new FunctionView();
      menu->setSwitchViewCallback(ModeManager::setMode); // set callback before swapping
      newView = menu;
      break;
    }
    case MODE_NEWS:
      newView = new NewsView();
      break;
    case MODE_NETWORK:
      newView = new DefaultView(); // placeholder
      break;
    default:
      newView = new DefaultView();
      break;
    }

    if (newView)
      newView->onEnter();

    currentView = newView;

    if (oldView)
    {
      oldView->onExit();
      delete oldView;
    }
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

  View *getCurrentView()
  {
    return currentView;
  }
}
