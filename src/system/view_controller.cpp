#include "view_controller.h"


ViewController::ViewController(IViewRenderer& renderer) : _renderer(renderer), _currentView(nullptr) {
  // Initialize the view controller with the renderer
}

void ViewController::addView(View* view) {
  views.push_back(view);
}

void ViewController::switchTo(int index) {

  _renderer.clear(); // Clear the renderer before switching views
  Serial.printf("ViewController::switchTo(%d)\n", index);
  Serial.printf("Total views: %d\n", views.size());

  if (views.empty()) {
    Serial.println("No views available to switch to.");
    return;
  }

  if (index < 0 || index >= views.size()) {
    Serial.println("Invalid view index.");
    return;
  }

  if (_currentView) {
    _currentView->onExit();
  }

  _currentView = views[index];
  if (_currentView) {
    Serial.println("Calling onEnter() for new view.");
    _currentView->onEnter();
  }
  else {
    Serial.println("currentView is null after switch.");
  }
}


View* ViewController::getCurrentView() const
{
  if (_currentView == nullptr) {
    Serial.println("No current view set.");
    return nullptr;
  }
  return _currentView;
}