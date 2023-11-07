#pragma once

namespace Widgets{

class Transform {
    public:
        Transform(int x, int y, int width, int height) 
            : x{x}, y{y}, width{width}, height{height} {}

        int getX() const { return x; }
        int getY() const { return y; }
        int getWidth() const { return width; }
        int getHeight() const { return height; }

        void setX(int x) { this->x = x; }
        void setY(int y) { this->y = y; }
        void setWidth(int width) { this->width = width; }
        void setHeight(int height) { this->height = height; }
    
    private:
        int x;
        int y;
        int width;
        int height;
};

}