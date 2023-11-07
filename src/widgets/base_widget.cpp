#include <ostream>
#include "base_widget.h"


namespace Widgets {

std::ostream& operator<<(std::ostream& out, const BaseWidget& widget) {
    out << "BaseWidget -";
    out << "(x, y) = (";
    out << widget.getX();
    out << ", ";
    out << widget.getY();
    out << ") :";
    out << "(width, height) = (";
    out << widget.getWidth();
    out << ", ";
    out << widget.getHeight();
    out << ")";

    return out;
}

}