#pragma once
#include "view.h"
#include "../interfaces/IViewRenderer.h"/
namespace Views
{
    class DefaultView : public View
    {

    public:
        void render() override;
        DefaultView(IViewRenderer& renderer) : _renderer(renderer) {}

    private:
        IViewRenderer& _renderer;
        bool showingClimate = false;
        unsigned long lastToggle = 0;
    };

}
