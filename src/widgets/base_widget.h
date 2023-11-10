#pragma once

#include <ostream>
#include <vector>
#include <SDL.h>
#include "transform.h"

namespace Widgets{

class BaseWidget : public Transform {
    public:
        BaseWidget(Transform transform) : Transform(transform) {}
        void add(BaseWidget* widget) { children.push_back(widget); }

        virtual void render(SDL_Renderer* renderer) const {};
        virtual void update() {};
        friend std::ostream& operator<< (std::ostream& out, const BaseWidget& widget);

        std::vector<BaseWidget*> children;
};

}