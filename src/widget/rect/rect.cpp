#include <iostream>
#include <SDL.h>
#include <string>
#include "rect.h"

namespace Widget{

void Rect::render(SDL_Renderer* renderer) const {
    SDL_Rect rect { getX(), getY(), getWidth(), getHeight() };
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
    const int result = SDL_RenderFillRect(renderer, &rect);
}

void Rect::update() {}

void Rect::toStringPrint() const {
    std::string out = "Rect - ";
    out += "(x, y) = (";
    out += std::to_string(this->getX());
    out += ", ";
    out += std::to_string(this->getY());
    out += ") :";
    out += "(width, height) = (";
    out += std::to_string(this->getWidth());
    out += ", ";
    out += std::to_string(this->getHeight());
    out += ")";

    std::cout << out;
}

}