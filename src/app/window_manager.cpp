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
      w_id {SDL_GetWindowID(window.get())} {

    std::cout << "window {" << getW_Id() << "} created" << std::endl;
}

WindowManager::~WindowManager() {
    std::cout << "window {" << getW_Id() << "} destroyed" << std::endl;
    print();
    deleteWidgetTree(root);
}

void WindowManager::render() {
    if(renderer) {
        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer.get());

        renderWidgetTree(root);

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
                        if(m_event.window.windowID == getW_Id() ) {
                            del_windows.insert(getW_Id());
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
        updateWidgetTree(root);
    }

    return -1;
}

void WindowManager::deleteWidgetTree(Widgets::BaseWidget const* widget) {
    if(widget) {
        for(Widgets::BaseWidget const* child: widget->children) {
            deleteWidgetTree(child);
        }

        delete widget;
        widget = nullptr;
    }
}

void WindowManager::updateWidgetTree(Widgets::BaseWidget* widget) { 
    if(widget) {
        widget->update();
        for(Widgets::BaseWidget* child: widget->children) {
            updateWidgetTree(child);
        }
    }
}

void WindowManager::renderWidgetTree(Widgets::BaseWidget const* widget) {
    if(widget && renderer) {
        widget->render(renderer.get());
        for(Widgets::BaseWidget const* child: widget->children) {
            renderWidgetTree(child);
        }
    }
}

void WindowManager::printWidgetTree(Widgets::BaseWidget const* widget, int level) {
    if(widget) {
        for(int i = 0; i < level; i++) {
            std::cout << "\t";
        }
        std::cout << *widget << std::endl;
        for(Widgets::BaseWidget const* child: widget->children) {
            printWidgetTree(child, level + 1);
        }
    }
}

}