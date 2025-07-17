//
//  Main.cpp
//  Warlock-macOS
//
//  Created by Abe Pralle on 1/22/24.
//

#include <cstdio>

#import "RogueInterface.h"

#include <iostream>
using namespace std;

#include <SDL2/SDL.h>
//SDL_Window *window;
//const char* window_name = "example SDL2 Vulkan application";


//#include <bgfx/bgfx.h>
//#include <bgfx/platform.h>
//#include <bx/math.h>

//#include <glm/mat4x4.hpp>
//#include <glm/vec3.hpp>
//#include <glm/vec4.hpp>
//using namespace glm;

/*
struct WarlockEventHandler : EventHandler
{
  bool begin_render( Window* window, unsigned char** render_data, int* count )
  {
    RogueByteList* list = WarlockWarlock__begin_render__RogueInt_RogueInt_RogueInt(
      window->index, window->width, window->height
    );
    if ( !list ) return false;
    *render_data = list->as_bytes;
    *count = (int)list->count;
    return true;
  }

  void end_render( Window* window )
  {
    WarlockWarlock__end_render__RogueInt( window->index );
    Rogue_check_gc();
  }
};
*/

bool handle_events()
{
  SDL_Event e;
  while(SDL_PollEvent(&e))
  {
    switch (e.type)
    {
      case SDL_QUIT:
        return false;

/*
      case SDL_WINDOWEVENT:
      {
        Window* window = find_window( e.window.windowID );
        if (window)
        {
          switch (e.window.event)
          {
            case SDL_WINDOWEVENT_MINIMIZED:
            case SDL_WINDOWEVENT_HIDDEN:
              window->rendering_paused = true;
              break;

            case SDL_WINDOWEVENT_RESTORED:
            case SDL_WINDOWEVENT_SHOWN:
              window->rendering_paused = false;
              break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
              // TODO
              break;
          }
        }
        break;
      }
*/

      /*
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
      {
        auto w = plasmacore_get_window(e.button.windowID);
        if (!w) break;
        int which;
        switch (e.button.button)
        {
          case SDL_BUTTON_LEFT:
            which = 0;
            break;
          case SDL_BUTTON_RIGHT:
            which = 1;
            break;
          default:
            return;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN)
          w->on_mouse_down(e.button.x, e.button.y, which);
        else
          w->on_mouse_up(e.button.x, e.button.y, which);
        break;
      }

      case SDL_MOUSEMOTION:
      {
        auto w = plasmacore_get_window(e.motion.windowID);
        if (!w) break;
        w->on_mouse_move(e.motion.x, e.motion.y);
        break;
      }

      case SDL_MOUSEWHEEL:
      {
        auto w = plasmacore_get_window(e.motion.windowID);
        if (!w) break;
        w->on_scroll(-e.wheel.x, e.wheel.y);
        break;
      }

      case SDL_KEYDOWN:
      {
        auto w = plasmacore_get_window(e.key.windowID);
        if (!w) break;
        w->on_key_event( e.key.keysym.scancode, true, !!e.key.repeat );
        break;
      }

      case SDL_KEYUP:
      {
        auto w = plasmacore_get_window(e.key.windowID);
        if (!w) break;
        w->on_key_event( e.key.keysym.scancode, false, false );
        break;
      }
      */

    }
  }
  return true;
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create SDL window
    SDL_Window* window = SDL_CreateWindow(
        "bgfx Triangle",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

