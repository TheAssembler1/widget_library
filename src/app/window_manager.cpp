#include <iostream>
#include <string>
#include <memory>
#include <functional>

#include "window_manager.h"
#include "SDL.h"

namespace App {

WindowManager::WindowManager(std::string title, int x, int y, int width, int height) 
    : window {std::unique_ptr<SDL_Window, SDLDestroyer>(SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_RESIZABLE))},
      renderer {std::unique_ptr<SDL_Renderer, SDLDestroyer>(SDL_CreateRenderer(window.get(), -1, 0))},
      window_id {static_cast<int>(SDL_GetWindowID(window.get()))} {

    if(!window) {
        std::cerr << "failed to create window" << std::endl;
    }

    if(!renderer) {
        std::cerr << "failed to create renderer" << std::endl;
    }
    
    SDL_GetWindowSize(window.get(), &window_width, &window_height);
    SDL_GetWindowPosition(window.get(), &window_x, &window_y);

    std::cout << *this << " created" << std::endl;
}

WindowManager::~WindowManager() {
    std::cout << *this << " destroyed" << std::endl;
    print();
    delete_widget_tree(root);
}

void WindowManager::render() const {
    if(renderer) {
        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer.get());

        render_widget_tree(root);

        SDL_RenderPresent(renderer.get());
    }
}

void WindowManager::update(std::vector<SDL_Event> events) {
    if(root) {
        update_widget_tree(root);
    }
}

void WindowManager::delete_widget_tree(Widgets::BaseWidget const* widget) {
    if(widget) {
        for(Widgets::BaseWidget const* child: widget->children) {
            delete_widget_tree(child);
        }

        delete widget;
        widget = nullptr;
    }
}

void WindowManager::update_widget_tree(Widgets::BaseWidget* const widget) { 
    if(widget) {
        widget->update();
        for(Widgets::BaseWidget* child: widget->children) {
            update_widget_tree(child);
        }
    }
}

void WindowManager::render_widget_tree(Widgets::BaseWidget const* const widget) const {
    if(widget && renderer) {
        widget->render(renderer.get());
        for(Widgets::BaseWidget const* child: widget->children) {
            render_widget_tree(child);
        }
    }
}

void WindowManager::print_widget_tree(Widgets::BaseWidget const* const widget, int level) const {
    if(widget) {
        for(int i = 0; i < level; i++) {
            std::cout << "\t";
        }
        std::cout << *widget << std::endl;
        for(Widgets::BaseWidget const* child: widget->children) {
            print_widget_tree(child, level + 1);
        }
    }
}

std::ostream& operator<<(std::ostream& out, const WindowManager& window_manager) {
    out << "window {" << window_manager.get_window_id() << "} ";
    out << "(x, y) = (" << window_manager.window_x << ", " << window_manager.window_y << ") : ";
    out << "(width, height) = (" << window_manager.window_width << ", " << window_manager.window_height << ")";;
    return out;
}

}