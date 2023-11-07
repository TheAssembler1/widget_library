#include <iostream>
#include <string>
#include <memory>
#include <functional>

#include "window_manager.h"
#include "SDL2/SDL.h"

namespace App {

WindowManager::WindowManager(std::string title, int x, int y, int width, int height) 
    : window {std::unique_ptr<SDL_Window, SDLDestroyer>(SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_RESIZABLE))},
      renderer {std::unique_ptr<SDL_Renderer, SDLDestroyer>(SDL_CreateRenderer(window.get(), -1, 0))},
      window_id {SDL_GetWindowID(window.get())} {

    std::cout << "window {" << get_window_id() << "} created" << std::endl;
}

WindowManager::~WindowManager() {
    std::cout << "window {" << get_window_id() << "} destroyed" << std::endl;
    print();
    delete_widget_tree(root);
}

void WindowManager::render() {
    if(renderer) {
        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer.get());

        render_widget_tree(root);

        SDL_RenderPresent(renderer.get());
    }
}

int WindowManager::update(std::vector<SDL_Event> events, std::set<int>& del_windows) {
    Uint32 w_flags = SDL_GetWindowFlags(window.get());

    bool closed = false;
    for(auto m_event: events) {
        switch (m_event.type) {
            case SDL_KEYDOWN:
                switch (m_event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        closed = true;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_WINDOWEVENT:
                switch (m_event.window.event) {
                    case SDL_WINDOWEVENT_CLOSE:
                        if(m_event.window.windowID == get_window_id() ) {
                            del_windows.insert(get_window_id());
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    if(root) {
        update_widget_tree(root);
    }

    return -1;
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

void WindowManager::update_widget_tree(Widgets::BaseWidget* widget) { 
    if(widget) {
        widget->update();
        for(Widgets::BaseWidget* child: widget->children) {
            update_widget_tree(child);
        }
    }
}

void WindowManager::render_widget_tree(Widgets::BaseWidget const* widget) {
    if(widget && renderer) {
        widget->render(renderer.get());
        for(Widgets::BaseWidget const* child: widget->children) {
            render_widget_tree(child);
        }
    }
}

void WindowManager::print_widget_tree(Widgets::BaseWidget const* widget, int level) {
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

}