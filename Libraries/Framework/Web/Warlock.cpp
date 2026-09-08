// Warlock.cpp - Web (Emscripten) entry point.
//
// Copied from Libraries/Warlock/Libraries/Framework/Web/Warlock.cpp into
// Platforms/Web/ - yours to modify; 'rogo deps' will not overwrite it.
//
// Uses SDL3's main-callback model, which on Emscripten drives the frame loop
// via emscripten_set_main_loop() so the browser never blocks.

#include <cstdio>
#include <cstdlib>

#include <SDL3/SDL.h>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include <bgfx/bgfx.h>
#include <emscripten.h>

#include "RogueProgram-Web.h"

SDL_AppResult SDL_AppInit( void** appstate, int argc, char* argv[] )
{
  *appstate = NULL;

  Rogue_configure( argc, argv );
  Rogue_launch();
  RogueWarlockWarlock__configure();

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate( void* appstate )
{
  static bool first_frame = true;

  RogueWarlockWarlock__tick();
  Rogue_check_gc();

  if (first_frame)
  {
    // Tell the loading screen in index.html that the app is up and drawing.
    first_frame = false;
    EM_ASM({ if (Module.onFirstFrame) Module.onFirstFrame(); });
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent( void* appstate, SDL_Event* event )
{
  Warlock_sdl_event = event;
  RogueLogical is_running = RogueWarlockWarlock__handle_event();
  return is_running ? SDL_APP_CONTINUE : SDL_APP_SUCCESS;
}

void SDL_AppQuit( void* appstate, SDL_AppResult result )
{
  bgfx::frame();
  bgfx::frame();
  bgfx::shutdown();
  SDL_Quit();
}
