#include <iostream>
#include <string>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "app/manager.h"
#include "app/window_manager.h"
#include "widget/rect/rect.h"
#include "widget/attr/transform.h"
#include "widget/attr/color.h"
#include "widget/container/h_container.h"

int main(int argc, const char* argv[]) {
    App::Manager manager;
    manager.init_app();

    App::WindowManager* window_manager_1 = new App::WindowManager(std::string("WidgetApp1"), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 720);


    Widget::HContainer* h_container = new Widget::HContainer();

    Widget::Rect* rect1 = new Widget::Rect(Widget::Transform { 0, 0, 10,  10 }, Widget::Color {255, 255, 255, 255});
    Widget::Rect* rect2 = new Widget::Rect(Widget::Transform { 100, 0, 10,  10 }, Widget::Color {255, 0, 0, 255});
    Widget::Rect* rect3 = new Widget::Rect(Widget::Transform { 100, 100, 10,  10 }, Widget::Color {0, 255, 0, 255});
    Widget::Rect* rect4 = new Widget::Rect(Widget::Transform { 0, 100, 10,  10 }, Widget::Color {0, 0, 255, 255});

    window_manager_1->init_root_widget(h_container);

    h_container->add(rect1);
    h_container->add(rect2);
    h_container->add(rect3);
    h_container->add(rect4);

    manager.addWindowManager(window_manager_1);

    manager.run();

    return 0;
}