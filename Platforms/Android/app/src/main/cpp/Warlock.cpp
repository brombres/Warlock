// app/src/main/cpp/sdl_bgfx_vulkan_main.cpp

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>     // not strictly required for bgfx, but handy
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <cstdio>

#include <SDL3/SDL_system.h>
#include <jni.h>

#include "Rogue/RogueProgram-Android.h"

// Entry point called from SDLActivity on Android
extern "C" int SDL_main( int argc, char* argv[] )
{
  Rogue_configure( argc, argv );
  Rogue_launch();
  RogueWarlockWarlock__configure();

  RogueLogical is_running = true;
  SDL_Event event;

  while (is_running)
  {
    while (SDL_PollEvent(&event))
    {
      Warlock_sdl_event = &event;
      is_running = RogueWarlockWarlock__handle_event();
    }

    RogueWarlockWarlock__tick();
    Rogue_check_gc();
  }

  bgfx::frame();
  bgfx::frame();

  bgfx::shutdown();
  SDL_Quit();

  return 0;
}

