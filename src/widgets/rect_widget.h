#pragma once

#include "base_widget.h"
#include "color.h"

namespace Widgets{

class RectWidget : public Widgets::BaseWidget {
    public:
        RectWidget(Transform transform, Color color) : BaseWidget(transform), color(color) {}

        void update() override;
        void render(SDL_Renderer* renderer) const override;

        const Color color;
};

}