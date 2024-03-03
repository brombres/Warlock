#include "Balefire/Balefire.h"
#include "Balefire/SDL/FrameworkSDLVulkan.h"
#include "Balefire/SDL/WindowFrameworkContextSDL.h"
#include "Balefire/Vulkan/RendererVulkan.h"
#include "Balefire/Vulkan/WindowRendererContextVulkan.h"
using namespace BALEFIRE;

void FrameworkSDLVulkan::configure()
{
  SDL_Init( SDL_INIT_VIDEO );
  renderer = new RendererVulkan( this );
  renderer->configure();
}

WindowID FrameworkSDLVulkan::create_window( String name )
{
  SDL_WindowFlags flags = (SDL_WindowFlags)(SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);

  SDL_Window* sdl_window =
    SDL_CreateWindow(
      name,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      1024,
      768,
      flags
    );

  Window* window = new Window();
  WindowFrameworkContextSDL* framework_context = new WindowFrameworkContextSDL( sdl_window );
  WindowRendererContextVulkan* renderer_context = new WindowRendererContextVulkan();
  window->framework_context = framework_context;
  window->renderer_context = renderer_context;

  window->id = balefire->windows.add( window );
  printf("window id:%d\n",window->id);

  RendererVulkan* renderer = (RendererVulkan*)this->renderer.data;
  if (SDL_TRUE != SDL_Vulkan_CreateSurface(
      framework_context->sdl_window,
      renderer->vulkan_instance,
      &renderer_context->surface
    ))
  {
    fprintf( stderr, "[ERROR] SDL_Vulkan_CreateSurface() failed.\n" );
  }

  renderer->configure_window( window );

  return window->id;
}

