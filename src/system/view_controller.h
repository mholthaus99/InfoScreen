#pragma once

#include <Arduino.h>

#include <vector>

#include "../interfaces/IView.h"
#include "../interfaces/IViewRenderer.h"

class ViewController {
   public:
    explicit ViewController(IViewRenderer& renderer);

    View* getCurrentView() const;
    void addView(View* view);
    void switchTo(int index);  // new method

   private:
    View* _currentView = nullptr;
    IViewRenderer& _renderer;
    std::vector<View*> views;
};
