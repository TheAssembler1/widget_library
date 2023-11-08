#include <SDL2/SDL.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <thread>
#include <set>
#include <cassert>
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
        std::this_thread::sleep_for (std::chrono::milliseconds(100));

        std::vector<SDL_Event> events;
        std::set<int> del_windows;

        poll_events(running, events, del_windows);

        for(auto manager_key_pair: multi_window_manager) {
            manager_key_pair.second->render(); 
            manager_key_pair.second->update(events);
        }
        
        events.clear();
        
        std::set<int>::const_iterator del_win_iter = del_windows.cbegin();
        while(del_win_iter != del_windows.cend()) {
            int win_id = *del_win_iter;

            auto it = multi_window_manager.find(win_id);
            assert (it != multi_window_manager.end());
            delete it->second;
            multi_window_manager.erase(it);

            del_win_iter = del_windows.erase(del_win_iter);
        }

        if(multi_window_manager.size() <= 0) {
            running = false;
        }
    }
}

void Manager::poll_events(bool& running, std::vector<SDL_Event>& events, std::set<int>& del_windows) {
    SDL_Event m_event;
    App::WindowManager* win_manager = nullptr; 
    std::unordered_map<int, App::WindowManager*>::iterator it;
    while(SDL_PollEvent(&m_event)) {
        switch (m_event.type) {
            case SDL_WINDOWEVENT:
                it = multi_window_manager.find(static_cast<int>(m_event.window.windowID));
                if(it == multi_window_manager.end()) {
                    continue;
                } else {
                    win_manager = multi_window_manager[m_event.window.windowID];
                }

                switch (m_event.window.event) {
                    case SDL_WINDOWEVENT_CLOSE:
                        win_manager->window_close_event(del_windows);
                        break;
                    case SDL_WINDOWEVENT_RESIZED:
                        win_manager->window_resized_event(m_event.window.data1, m_event.window.data2);
                        break;
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        win_manager->window_size_changed_event();
                        break;
                    case SDL_WINDOWEVENT_MOVED:
                        win_manager->window_moved_event(m_event.window.data1, m_event.window.data2);
                        break;
                    default:
                        break;
                }
                break;
            default:
                // FIXME: need to match event with window that has focus
                events.push_back(m_event);
                break;
        }
    }
}

}