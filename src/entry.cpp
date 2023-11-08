#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <thread>
#include <chrono> 
#include <vector>
#include <unordered_map>
#include "app/manager.h"
#include "app/window_manager.h"
#include "widgets/rect_widget.h"
#include "widgets/transform.h"
#include "widgets/color.h"

int main() {
    App::Manager manager;
    manager.init_app();

    App::WindowManager* window_manager_1 = new App::WindowManager(std::string("WidgetApp1"), 0, 0, 1200, 720);
    //App::WindowManager* window_manager_2 = new App::WindowManager(std::string("WidgetApp2"), 0, 0, 200, 200);
    //App::WindowManager* window_manager_3 = new App::WindowManager(std::string("WidgetApp3"), 0, 0, 200, 200);
    //App::WindowManager* window_manager_4 = new App::WindowManager(std::string("WidgetApp4"), 0, 0, 200, 200);
    //App::WindowManager* window_manager_5 = new App::WindowManager(std::string("WidgetApp5"), 0, 0, 200, 200);
    //App::WindowManager* window_manager_6 = new App::WindowManager(std::string("WidgetApp6"), 0, 0, 200, 200);

    Widgets::RectWidget* root = new Widgets::RectWidget(Widgets::Transform { 0, 0, 10,  10 }, Widgets::Color {255, 255, 255, 255});
    Widgets::RectWidget* root1 = new Widgets::RectWidget(Widgets::Transform { 100, 0, 10,  10 }, Widgets::Color {255, 0, 0, 255});
    Widgets::RectWidget* root2 = new Widgets::RectWidget(Widgets::Transform { 100, 100, 10,  10 }, Widgets::Color {0, 255, 0, 255});
    Widgets::RectWidget* root3 = new Widgets::RectWidget(Widgets::Transform { 0, 100, 10,  10 }, Widgets::Color {0, 0, 255, 255});

    window_manager_1->init_root_widget(root);
    root->add(root1);
    root->add(root2);
    root->add(root3);

    manager.addWindowManager(window_manager_1);
           /*.addWindowManager(window_manager_2)
           .addWindowManager(window_manager_3)
           .addWindowManager(window_manager_4)
           .addWindowManager(window_manager_5)
           .addWindowManager(window_manager_6);*/

    manager.run();

    return 0;
}