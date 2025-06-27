#include "view_controller.h"
#include "../views/default_view.h"
#include "../views/news_view.h"
#include "../views/menu_view.h"

using namespace Views;

ViewController::ViewController(LcdRenderer& renderer)
  : renderer(renderer) {
}

void ViewController::switchView(DisplayMode mode) {
  View* oldView = currentView;
  View* newView = nullptr;

  currentMode = mode;

  switch (mode) {
  case MODE_DEFAULT:
    newView = new DefaultView(renderer);
    break;
  case MODE_MENU: {
    auto* menu = new FunctionView();
    menu->setSwitchViewCallback([this](DisplayMode m) { this->setMode(m); });
    newView = menu;
    break;
  }
  case MODE_NEWS:
    newView = new NewsView();
    break;
  case MODE_NETWORK:
    newView = new DefaultView(renderer); // Placeholder
    break;
  default:
    newView = new DefaultView(renderer);
    break;
  }

  if (newView)
    newView->onEnter();

  currentView = newView;

  if (oldView) {
    oldView->onExit();
    delete oldView;
  }
}

void ViewController::setMode(DisplayMode mode) {
  switchView(mode);
}

DisplayMode ViewController::getMode() const {
  return currentMode;
}

View* ViewController::getCurrentView() const {
  return currentView;
}
