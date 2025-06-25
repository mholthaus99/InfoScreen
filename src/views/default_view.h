#pragma once
#include "view.h"

namespace Views
{

    class DefaultView : public View
    {
    private:
        bool showingClimate = false;
        unsigned long lastToggle = 0;

    public:
        void render() override;
    };

}
