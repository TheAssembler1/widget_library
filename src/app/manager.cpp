#include <SDL2/SDL.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <thread>
#include <set>
#include "window_manager.h"
#include "manager.h"

namespace App {

void Manager::init_app() {
    assert(SDL_Init(SDL_INIT_VIDEO) <= 0);
    std::cout << "succesfully initialized SDL2 with flags: " << SDL_INIT_VIDEO << std::endl;
}

Manager& Manager::addWindowManager(App::WindowManager* window_manager) {
    std::cout << "window {" << window_manager->get_window_id() << "} added to manager" << std::endl;
    multi_window_manager.insert({window_manager->get_window_id(), window_manager});

    return *this;
}


void Manager::run() {
    bool running = true;

    while(running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); 


        std::vector<SDL_Event> events;
        poll_events(running, events);

        // NOTE: mark windows for deletion
        std::set<int> del_windows;

        for(auto manager_key_pair: multi_window_manager) {
            manager_key_pair.second->render(); 
            manager_key_pair.second->update(events, del_windows);
        }
        
        events.clear();
        
        std::set<int>::const_iterator del_win_iter = del_windows.cbegin();
        while(del_win_iter != del_windows.cend()) {
            App::WindowManager* win = multi_window_manager[*del_win_iter];
            delete win;
            multi_window_manager.erase(*del_win_iter);
            del_win_iter = del_windows.erase(del_win_iter);
        }

        if(multi_window_manager.size() <= 0) {
            running = false;
        }
    }
}

void Manager::poll_events(bool& running, std::vector<SDL_Event>& events) {
    SDL_Event m_event;
    while(SDL_PollEvent(&m_event)) {
        events.push_back(m_event);
    }
}

}