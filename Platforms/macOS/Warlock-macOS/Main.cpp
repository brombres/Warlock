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

/*
int main( int argc, char *argv[] )
{
  Balefire balefire( new FrameworkSDLVulkan() );
  balefire.create_window( "Warlock Engine" );

  bool bQuit = false;

  // main loop
  while (!bQuit)
  {
    // Handle events on queue
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
      // close the window when user alt-f4s or clicks the X button
      if (e.type == SDL_QUIT)
        bQuit = true;

      //if (e.type == SDL_WINDOWEVENT) {
      //  if (e.window.event == SDL_WINDOWEVENT_MINIMIZED) {
      //    stop_rendering = true;
      //  }
      //  if (e.window.event == SDL_WINDOWEVENT_RESTORED) {
      //    stop_rendering = false;
      //  }
      //}
    }

    // do not draw if we are minimized
    //if (stop_rendering) {
    //  // throttle the speed to avoid the endless spinning
    //  std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //  continue;
    //}

    balefire.render();
  }

  printf("Success\n");

  return 0;
}
*/

#include <iostream>
using namespace std;

#include <SDL2/SDL.h>
SDL_Window *window;
char* window_name = "example SDL2 Vulkan application";

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
using namespace glm;

#include "VulkanInterface.h"
#include "VulkanFunctions.h"
Vulkan *vulkan;

int main(int argc, char *argv[])
{
  Balefire balefire( new FrameworkSDLVulkan() );
  balefire.create_window( "Warlock Engine" );

  vulkan = new Vulkan();
  init_vulkan_extern(vulkan);

	//const array of positions for the triangle
	const vec3 positions[3] = {
		vec3(1.f,1.f, 0.0f),
		vec3(-1.f,1.f, 0.0f),
		vec3(0.f,-1.f, 0.0f)
	};

  SDL_Event event;
  bool running = true;
  while(running)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        running = false;
      }
    }

    AcquireNextImage();

    ResetCommandBuffer();
    BeginCommandBuffer();
    {
      VkClearColorValue clear_color = {0.0f, 0.0f, 1.0f, 1.0f};
      VkClearDepthStencilValue clear_depth_stencil = {1.0f, 0};
      BeginRenderPass(clear_color,clear_depth_stencil);
      {

      }
      EndRenderPass();
    }
    EndCommandBuffer();

    QueueSubmit();
    QueuePresent();
    balefire.render();
  }

  delete vulkan;
  vulkan = nullptr;

  //SDL_DestroyWindow(window);
  //window = nullptr;

  SDL_Quit();
  return 0;
}
