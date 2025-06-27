#pragma once

#include "../interfaces/IViewRenderer.h"
#include "../views/view.h"
#include <vector>

enum DisplayMode {
     MODE_DEFAULT,
     MODE_MENU,
     MODE_NEWS,
     MODE_NETWORK
};

class ViewController {
public:
     explicit ViewController(IViewRenderer& renderer);

     void setMode(DisplayMode mode);
     DisplayMode getMode() const;
     View* getCurrentView() const;
     void addView(View* view) {
          views.push_back(view);
     }

private:
     void switchView(DisplayMode mode);

     DisplayMode currentMode = MODE_DEFAULT;
     View* currentView = nullptr;
     IViewRenderer& _renderer;
     std::vector<View*> views;
};
