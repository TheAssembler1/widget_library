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
        void init_root_widget(Widgets::BaseWidget* const widget) { root = widget; }

        void update(std::vector<SDL_Event> events);
        void render() const;

        void print() const { if(root) { print_widget_tree(root, 0); } }

        Uint32 get_window_id() const { return window_id; }

        bool is_window_fullscreen_flag() const { return IS_WINDOW_FULLSCREEN(window.get()); }
        bool is_window_fullscreen_desktop_flag() const { return IS_WINDOW_FULLSCREEN_DESKTOP(window.get()); }
        bool is_window_opengl_flag() const { return IS_WINDOW_OPENGL(window.get()); }
        bool is_window_vulkan_flag() const { return IS_WINDOW_VULKAN(window.get()); }
        bool is_window_shown_flag() const { return IS_WINDOW_SHOWN(window.get()); }
        bool is_window_hidden_flag() const { return IS_WINDOW_HIDDEN(window.get()); }
        bool is_window_borderless_flag() const { return IS_WINDOW_BORDERLESS(window.get()); }
        bool is_window_resizable_flag() const { return IS_WINDOW_RESIZABLE(window.get()); }
        bool is_window_minimized_flag() const { return IS_WINDOW_MINIMIZED(window.get()); }
        bool is_window_input_maximized_flag() const { return IS_WINDOW_MAXIMIZED(window.get()); }
        bool is_window_input_grabbed_flag() const { return IS_WINDOW_INPUT_GRABBED(window.get()); }
        bool is_window_input_focus_flag() const { return IS_WINDOW_INPUT_FOCUS(window.get()); }
        bool is_window_mouse_focus_flag() const { return IS_WINDOW_MOUSE_FOCUS(window.get()); }
        bool is_window_foreign_flag() const { return IS_WINDOW_FOREIGN(window.get()); }
        bool is_window_allow_highdpi_flag() const { return IS_WINDOW_ALLOW_HIGHDPI(window.get()); }
        bool is_window_mouse_capture_flag() const { return IS_WINDOW_MOUSE_CAPTURE(window.get()); }
        bool is_window_always_on_top_flag() const { return IS_WINDOW_ALWAYS_ON_TOP(window.get()); }
        bool is_window_skip_taskbar_flag() const { return IS_WINDOW_SKIP_TASKBAR(window.get()); }
        bool is_window_utility_flag() const { return IS_WINDOW_UTILITY(window.get()); }
        bool is_window_tooltip_flag() const { return IS_WINDOW_TOOLTIP(window.get()); }
        bool is_window_popup_screen_flag() const { return IS_WINDOW_POPUP_SCREEN(window.get()); }

        //void window_shown_event() {}
        //void window_hidden_event() {}
        void window_moved_event(int n_x, int n_y) {
            window_x = n_x;
            window_y = n_y;
        }
        void window_resized_event(int n_width, int n_height ) { 
            this->window_width = n_width;
            this->window_height = n_height;
        }
        void window_size_changed_event() { 
            manually_update_window_position();
        }
        //void window_minimized_event() {}
        //void window_maximized_event() {}
        //void window_restored_event() {}
        void window_close_event(std::set<int>& del_windows) { del_windows.insert(get_window_id()); }
        //void window_take_focus_event() {}
        //void window_hit_test_event() {}
        //void window_iccprof_changed() {}
        //void window_display_changed() {}

        friend std::ostream& operator<<(std::ostream& out, const WindowManager& window_manager);
    private:
        void update_widget_tree(Widgets::BaseWidget* const widget);
        void render_widget_tree(Widgets::BaseWidget const* const widget) const;
        void print_widget_tree(Widgets::BaseWidget const* const widget, int level) const;
        void delete_widget_tree(Widgets::BaseWidget const* const widget);

        void manually_update_window_position() {
            SDL_GetWindowPosition(window.get(), &window_x, &window_y);
        }

        std::unique_ptr<SDL_Window, SDLDestroyer> window;
        std::unique_ptr<SDL_Renderer, SDLDestroyer> renderer;
        Widgets::BaseWidget* root = nullptr;

        // NOTE: SDL2 window id
        int window_id = 0;

        int window_width = 0;
        int window_height = 0;
        int window_x = 0;
        int window_y = 0;
};

}