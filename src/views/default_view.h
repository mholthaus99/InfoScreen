#pragma once
#include "view.h"
#include "../interfaces/IViewRenderer.h"
#include "../interfaces/ITime.h"
namespace Views
{
    class DefaultView : public View
    {

    public:
        void render() override;
        DefaultView(IViewRenderer& renderer, ITime& time) : _renderer(renderer), _time(time){}

    private:
        IViewRenderer& _renderer;
        ITime& _time;
        bool showingClimate = false;
        unsigned long lastToggle = 0;
    };

}
