#pragma once
#include <Arduino.h>

#include "../interfaces/IViewRenderer.h"
#include "../views/view.h"

#include "ir_receiver.h"
#include "view_controller.h"


class Controller {
public:
  
    Controller(IViewRenderer& viewRenderer);

    void init();

    void addView(View* view) {
        viewController.addView(view);
    }

    void loop();

private:

    IViewRenderer& _viewRenderer;
    ViewController viewController;

    IRReceiver irReceiver;

    void initIR();


 
    template <typename MethodPtr>
    void dispatchIRHandler(MethodPtr method) {
        if (auto view = viewController.getCurrentView()) {
            (view->*method)();
        }
    }

    template <typename MethodPtr, typename Arg>
    void dispatchIRHandler(MethodPtr method, Arg arg) {
        if (auto view = viewController.getCurrentView()) {
            (view->*method)(arg);
        }
    }




 



};