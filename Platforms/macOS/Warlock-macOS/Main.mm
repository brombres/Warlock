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

CmdData* begin_render_handler( Window* window, void* app_data )
{
  WarlockCmdDataList* list = WarlockWarlock__begin_render__RogueInt( window->index );
  if ( !list ) return nullptr;
  return (CmdData*)(list->data);
}

void end_render_handler( Window* window, void* app_data )
{
  WarlockWarlock__end_render__RogueInt( window->index );
}


int main(int argc, char *argv[])
{
  RogueInterface_configure( argc, argv );
  RogueInterface_launch();

  Balefire balefire( new FrameworkSDLVulkan() );
  balefire.set_render_handlers( begin_render_handler, end_render_handler );

  balefire.create_window( 1, "Warlock Engine" );

	//const array of positions for the triangle
	//const vec3 positions[3] = {
	//	vec3(1.f,1.f, 0.0f),
	//	vec3(-1.f,1.f, 0.0f),
	//	vec3(0.f,-1.f, 0.0f)
	//};

  while (balefire.handle_events()) balefire.render();


  SDL_Quit();
  return 0;
}
