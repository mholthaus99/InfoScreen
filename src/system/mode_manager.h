#pragma once
#include "views/view.h"


enum DisplayMode
{
  MODE_DEFAULT,
  MODE_MENU,
  MODE_NEWS,
  MODE_NETWORK,
  MODE_COUNT
};

namespace Views{
  class View;
}

namespace ModeManager
{
  void switchView(DisplayMode mode);
  void renderCurrentView();
  void setMode(DisplayMode mode);
  DisplayMode getMode();
  Views::View* getCurrentView();
  //View* getCurrentViewPointer(); // Renamed to avoid overloading by return type alone
}
