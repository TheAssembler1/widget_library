#pragma once

#include <string>
#include <memory>
#include <set>
#include <SDL2/SDL.h>
#include "../widgets/base_widget.h"

#define IS_WINDOW_FULLSCREEN(x) SDL_GetWindowFlags(x) & SDL_WINDOW_FULLSCREEN
#define IS_WINDOW_FULLSCREEN_DESKTOP(x) SDL_GetWindowFlags(x) & SDL_WINDOW_FULLSCREEN_DESKTOP
#define IS_WINDOW_OPENGL(x) SDL_GetWindowFlags(x) & SDL_WINDOW_OPENGL
#define IS_WINDOW_VULKAN(x) SDL_GetWindowFlags(x) & SDL_WINDOW_VULKAN
#define IS_WINDOW_SHOWN(x) SDL_GetWindowFlags(x) & SDL_WINDOW_SHOWN
#define IS_WINDOW_HIDDEN(x) SDL_GetWindowFlags(x) & SDL_WINDOW_HIDDEN
#define IS_WINDOW_BORDERLESS(x) SDL_GetWindowFlags(x) & SDL_WINDOW_BORDERLESS
#define IS_WINDOW_RESIZABLE(x) SDL_GetWindowFlags(x) & SDL_WINDOW_RESIZABLE
#define IS_WINDOW_MINIMIZED(x) SDL_GetWindowFlags(x) & SDL_WINDOW_MINIMIZED
#define IS_WINDOW_MAXIMIZED(x) SDL_GetWindowFlags(x) & SDL_WINDOW_MAXIMIZED
#define IS_WINDOW_INPUT_GRABBED(x) SDL_GetWindowFlags(x) & SDL_WINDOW_INPUT_GRABBED
#define IS_WINDOW_INPUT_FOCUS(x) SDL_GetWindowFlags(x) & SDL_WINDOW_INPUT_FOCUS
#define IS_WINDOW_MOUSE_FOCUS(x) SDL_GetWindowFlags(x) & SDL_WINDOW_MOUSE_FOCUS
#define IS_WINDOW_FOREIGN(x) SDL_GetWindowFlags(x) & SDL_WINDOW_FOREIGN
#define IS_WINDOW_ALLOW_HIGHDPI(x) SDL_GetWindowFlags(x) & SDL_WINDOW_ALLOW_HIGHDPI
#define IS_WINDOW_MOUSE_CAPTURE(x) SDL_GetWindowFlags(x) & SDL_WINDOW_MOUSE_CAPTURE
#define IS_WINDOW_ALWAYS_ON_TOP(x) SDL_GetWindowFlags(x) & SDL_WINDOW_ALWAYS_ON_TOP
#define IS_WINDOW_SKIP_TASKBAR(x) SDL_GetWindowFlags(x) & SDL_WINDOW_SKIP_TASKBAR
#define IS_WINDOW_UTILITY(x) SDL_GetWindowFlags(x) & SDL_WINDOW_UTILITY
#define IS_WINDOW_TOOLTIP(x) SDL_GetWindowFlags(x) & SDL_WINDOW_TOOLTIP
#define IS_WINDOW_POPUP_SCREEN(x) SDL_GetWindowFlags(x) & SDL_WINDOW_POPUP_MENU

namespace App {

struct SDLDestroyer
{
    void operator()(SDL_Window* w) const
    {
        SDL_DestroyWindow(w);
    }

    void operator()(SDL_Renderer* w) const
    {
        SDL_DestroyRenderer(w);
    }
};



class WindowManager {
    public: 
        WindowManager(std::string title, int x, int y, int width, int height);
        ~WindowManager();
        void initRootWidget(Widgets::BaseWidget* widget) {
            root = widget;
        }

        int update(std::vector<SDL_Event> events, std::set<int>& del_winodws);
        void render();

        void print() {
            if(root) {
                printWidgetTree(root, 0);
            }
        }

        Uint32 getW_Id() {
            return w_id;
        }

        bool is_window_fullscreen_flag() { return IS_WINDOW_FULLSCREEN(window.get()); }
        bool is_window_fullscreen_desktop_flag() { return IS_WINDOW_FULLSCREEN_DESKTOP(window.get()); }
        bool is_window_opengl_flag() { return IS_WINDOW_OPENGL(window.get()); }
        bool is_window_vulkan_flag() { return IS_WINDOW_VULKAN(window.get()); }
        bool is_window_shown_flag() { return IS_WINDOW_SHOWN(window.get()); }
        bool is_window_hidden_flag() { return IS_WINDOW_HIDDEN(window.get()); }
        bool is_window_borderless_flag() { return IS_WINDOW_BORDERLESS(window.get()); }
        bool is_window_resizable_flag() { return IS_WINDOW_RESIZABLE(window.get()); }
        bool is_window_minimized_flag() { return IS_WINDOW_MINIMIZED(window.get()); }
        bool is_window_input_maximized_flag() { return IS_WINDOW_MAXIMIZED(window.get()); }
        bool is_window_input_grabbed_flag() { return IS_WINDOW_INPUT_GRABBED(window.get()); }
        bool is_window_input_focus_flag() { return IS_WINDOW_INPUT_FOCUS(window.get()); }
        bool is_window_mouse_focus_flag() { return IS_WINDOW_MOUSE_FOCUS(window.get()); }
        bool is_window_foreign_flag() { return IS_WINDOW_FOREIGN(window.get()); }
        bool is_window_allow_highdpi_flag() { return IS_WINDOW_ALLOW_HIGHDPI(window.get()); }
        bool is_window_mouse_capture_flag() { return IS_WINDOW_MOUSE_CAPTURE(window.get()); }
        bool is_window_always_on_top_flag() { return IS_WINDOW_ALWAYS_ON_TOP(window.get()); }
        bool is_window_skip_taskbar_flag() { return IS_WINDOW_SKIP_TASKBAR(window.get()); }
        bool is_window_utility_flag() { return IS_WINDOW_UTILITY(window.get()); }
        bool is_window_tooltip_flag() { return IS_WINDOW_TOOLTIP(window.get()); }
        bool is_window_popup_screen_flag() { return IS_WINDOW_POPUP_SCREEN(window.get()); }

    private:
        void updateWidgetTree(Widgets::BaseWidget* widget);
        void renderWidgetTree(Widgets::BaseWidget const* widget);
        void printWidgetTree(Widgets::BaseWidget const* widget, int level);
        void deleteWidgetTree(Widgets::BaseWidget const* widget);

        std::unique_ptr<SDL_Window, SDLDestroyer> window;
        std::unique_ptr<SDL_Renderer, SDLDestroyer> renderer;
        Widgets::BaseWidget* root = nullptr;

        // NOTE: SDL2 window id
        Uint32 w_id = 0;
};

}