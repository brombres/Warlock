#include "Balefire/SDL/FrameworkSDLVulkan.h"
#include "Balefire/SDL/WindowSDLVulkan.h"
#include "Balefire/Vulkan/RendererVulkan.h"
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

  WindowSDLVulkan* window = new WindowSDLVulkan(
    SDL_CreateWindow(
      name,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      1024,
      768,
      flags
    )
  );

  //window->id = windows.add( window );

  RendererVulkan* renderer = (RendererVulkan*)this->renderer.data;
  printf( "window: %llx\n", (intptr_t)window );
  printf( "renderer: %llx\n", (intptr_t)renderer );
  auto result = SDL_Vulkan_CreateSurface(
    window->sdl_window,
    renderer->vulkan_instance,
    &window->vulkan_surface
  );
  printf( "success: %d\n", result == SDL_TRUE );

  renderer->configure_window( window );

  return window->id;
}

