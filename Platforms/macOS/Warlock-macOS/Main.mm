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
using namespace std;

#include <SDL2/SDL.h>
//SDL_Window *window;
//const char* window_name = "example SDL2 Vulkan application";

//#include <glm/mat4x4.hpp>
//#include <glm/vec3.hpp>
//#include <glm/vec4.hpp>
//using namespace glm;

bool begin_render_handler( Window* window, void* app_data, const char** render_data, int* count  )
{
  RogueByteList* list = WarlockWarlock__begin_render__RogueInt( window->index );
  if ( !list ) return false;
  *render_data = (const char*)list->data;
  *count = (int)list->count;
  return true;
}

void end_render_handler( Window* window, void* app_data )
{
  WarlockWarlock__end_render__RogueInt( window->index );
}


int main(int argc, char *argv[])
{
  Balefire balefire( new FrameworkSDLVulkan() );
  balefire.set_render_handlers( begin_render_handler, end_render_handler );

  RogueInterface_configure( argc, argv );
  RogueInterface_launch();

  while (balefire.handle_events()) balefire.render();


  SDL_Quit();
  return 0;
}
