#include <string>
#include <iostream>
#include "base_widget.h"


namespace Widget {

void BaseWidget::toStringPrint() const {
    std::string out =  "BaseWidget -";
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