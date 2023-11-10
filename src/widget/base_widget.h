#pragma once

#include <ostream>
#include <vector>
#include <SDL.h>
#include "attr/transform.h"

namespace Widget {

class BaseWidget : public Transform {
    public:
        BaseWidget(Transform transform) : Transform(transform) {}
        virtual void add(BaseWidget* widget) { children.push_back(widget); }

        virtual void render(SDL_Renderer* renderer) const {};
        virtual void update() {};
        virtual void toStringPrint () const;

        std::vector<BaseWidget*> children;
};

}