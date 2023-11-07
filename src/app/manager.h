#pragma once

#include "window_manager.h"
#include "SDL2/SDL.h"

namespace App {

class Manager {
    public:
        void init_app();
        void poll_events(bool& running, std::vector<SDL_Event>& events);
        void run();
        Manager& addWindowManager(App::WindowManager* window_manager);
    
    ~Manager() { 
        SDL_Quit();
    }

    private:
        std::unordered_map<int, App::WindowManager*> multi_window_manager;
};

}