#include "Balefire/SDL/FrameworkSDL.h"
#include "Balefire/SDL/WindowFrameworkContextSDL.h"
using namespace BALEFIRE;

void FrameworkSDL::configure()
{
  SDL_Init( SDL_INIT_VIDEO );
}

Window* FrameworkSDL::create_window( int index, std::string name )
{
  return nullptr;
}

Window* FrameworkSDL::find_window( Uint32 sdl_id )
{
  for (Window* cur : balefire->windows)
  {
    if (cur && ((WindowFrameworkContextSDL*)(cur->framework_context))->sdl_window_id == sdl_id)
    {
      return cur;
    }
  }
  return nullptr;
}

bool FrameworkSDL::handle_events()
{
  SDL_Event e;
  while(SDL_PollEvent(&e))
  {
    switch (e.type)
    {
      case SDL_QUIT:
        return false;

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
