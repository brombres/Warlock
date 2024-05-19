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
          if (e.window.event == SDL_WINDOWEVENT_MINIMIZED || e.window.event == SDL_WINDOWEVENT_HIDDEN)
          {
            window->rendering_paused = true;
            //printf("PAUSE RENDERING\n");
          }
          else if (e.window.event == SDL_WINDOWEVENT_RESTORED || e.window.event == SDL_WINDOWEVENT_SHOWN)
          {
            window->rendering_paused = false;
            //printf("RESUME RENDERING\n");
          }
        }
        break;
      }
    }
  }
  return true;
}
