#pragma once

#include <unordered_map>
#include "window_manager.h"
#include "SDL.h"

namespace App {

class Manager {
    public:
        void init_app();
        void poll_events(bool& running, std::vector<SDL_Event>& events, std::set<int>& del_windows);
        void run();
        Manager& addWindowManager(App::WindowManager* window_manager);
    
    ~Manager() { 
        SDL_Quit();
    }

    private:
        std::unordered_map<int, App::WindowManager*> multi_window_manager;
};

}