#include <iostream>
#include <string>
#include "h_container.h"

namespace Widget {

void HContainer::toStringPrint() const {
    std::string out = "HContainer - ";
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