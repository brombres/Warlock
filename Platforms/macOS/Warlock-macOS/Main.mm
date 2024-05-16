//
//  Main.cpp
//  Warlock-macOS
//
//  Created by Abe Pralle on 1/22/24.
//

#include <cstdio>

#include "Balefire/Balefire.h"
#include "Balefire/SDL/FrameworkSDLVulkan.h"
using namespace BALEFIRE;

#import "RogueInterface.h"

#include <iostream>
#include <thread>
using namespace std;

#include <SDL2/SDL.h>
//SDL_Window *window;
//const char* window_name = "example SDL2 Vulkan application";

//#include <glm/mat4x4.hpp>
//#include <glm/vec3.hpp>
//#include <glm/vec4.hpp>
//using namespace glm;

void on_render_begin( void* data )
{
}

void on_render( void* data )
{
}

void on_render_end( void* data )
{
}

int main(int argc, char *argv[])
{
  RogueInterface_configure( argc, argv );
  RogueInterface_launch();

  Balefire balefire( new FrameworkSDLVulkan() );
  balefire.create_window( "Warlock Engine" );

  balefire.on_render_begin = on_render_begin;
  balefire.on_render       = on_render;
  balefire.on_render_end   = on_render_end;

	//const array of positions for the triangle
	//const vec3 positions[3] = {
	//	vec3(1.f,1.f, 0.0f),
	//	vec3(-1.f,1.f, 0.0f),
	//	vec3(0.f,-1.f, 0.0f)
	//};

  SDL_Event e;
  bool running = true;
  bool pause_rendering = false;
  while(running)
  {
    while(SDL_PollEvent(&e))
    {
      switch (e.type)
      {
        case SDL_QUIT:
          running = false;
          break;

        case SDL_WINDOWEVENT:
          if (e.window.event == SDL_WINDOWEVENT_MINIMIZED || e.window.event == SDL_WINDOWEVENT_HIDDEN)
          {
            printf("PAUSE RENDERING\n");
            pause_rendering = true;
          }
          else if (e.window.event == SDL_WINDOWEVENT_RESTORED || e.window.event == SDL_WINDOWEVENT_SHOWN)
          {
            printf("RESUME RENDERING\n");
            pause_rendering = false;
          }
          break;
      }
    }

    if (pause_rendering) {
      std::this_thread::sleep_for( std::chrono::milliseconds(100) );
      continue;
    }

    balefire.render();
  }

  SDL_Quit();
  return 0;
}
