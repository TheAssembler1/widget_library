#include <iostream>
#include <SDL2/SDL.h>
#include "rect_widget.h"

namespace Widgets{

void RectWidget::render(SDL_Renderer* renderer) const {
    SDL_Rect rect { getX(), getY(), getWidth(), getHeight() };
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
    const int result = SDL_RenderFillRect(renderer, &rect);
}

void RectWidget::update() {
    setX(getX() + 1);
}

}