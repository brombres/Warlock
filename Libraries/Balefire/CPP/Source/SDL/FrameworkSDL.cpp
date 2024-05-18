#include "Balefire/SDL/FrameworkSDL.h"
using namespace BALEFIRE;

void FrameworkSDL::configure()
{
  SDL_Init( SDL_INIT_VIDEO );
}

Window* FrameworkSDL::create_window( int index, std::string name )
{
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
        if (e.window.event == SDL_WINDOWEVENT_MINIMIZED || e.window.event == SDL_WINDOWEVENT_HIDDEN)
        {
          printf("PAUSE RENDERING\n");
          //pause_rendering = true;
        }
        else if (e.window.event == SDL_WINDOWEVENT_RESTORED || e.window.event == SDL_WINDOWEVENT_SHOWN)
        {
          printf("RESUME RENDERING\n");
          //pause_rendering = false;
        }
        break;
    }
  }
  return true;
}
