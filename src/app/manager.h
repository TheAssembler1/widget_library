#pragma once

#include "window_manager.h"
#include "SDL2/SDL.h"

namespace App {

class Manager {
    public:
        void initApp();
        void pollEvents(bool& running, std::vector<SDL_Event>& events);
        void run();
        Manager& addWindowManager(App::WindowManager* windowManager);
    
    ~Manager() { 
        SDL_Quit();
    }

    private:
        std::unordered_map<int, App::WindowManager*> windowManagers;
};

}