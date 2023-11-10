#pragma once

#include "../base_widget.h"
#include "../attr/color.h"

namespace Widget{

class Rect : public Widget::BaseWidget {
    public:
        Rect(Transform transform, Color color) : BaseWidget(transform), color(color) {}

        void update() override;
        void render(SDL_Renderer* renderer) const override;
        void add(BaseWidget* widget) override {
            throw std::runtime_error("invalid add to rect widget");
        }
        void toStringPrint() const override;

        const Color color;
};

}