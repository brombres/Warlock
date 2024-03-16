#include "Balefire/Balefire.h"
#include "Balefire/SDL/FrameworkSDLVulkan.h"
#include "Balefire/SDL/WindowFrameworkContextSDL.h"
#include "Balefire/Vulkan/RendererVulkan.h"
#include "Balefire/Vulkan/WindowRenderContextVulkan.h"
using namespace BALEFIRE;

#include <vector>

void FrameworkSDLVulkan::configure()
{
  SDL_Init( SDL_INIT_VIDEO );
  renderer = new RendererVulkan( this );
  renderer->configure();
}

WindowID FrameworkSDLVulkan::create_window( String name )
{
  int w = 1024;
  int h = 768;

  int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE;

  SDL_Window* sdl_window =
    SDL_CreateWindow(
      name,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      w,
      h,
      flags
    );

  //unsigned int extensionCount = 0;
  //SDL_Vulkan_GetInstanceExtensions(sdl_window, &extensionCount, nullptr);
  //std::vector<const char *> extensionNames(extensionCount);
  //SDL_Vulkan_GetInstanceExtensions(sdl_window, &extensionCount, extensionNames.data());
  //printf("SDL REQUIRED VULKAN INSTANCE EXTENSIONS:%d\n",extensionCount);
  //for (int i=0; i<extensionCount; ++i)
  //{
  //  printf( "%d %s\n",i,extensionNames[i] );
  //}


  RendererVulkan* renderer = (RendererVulkan*)this->renderer.data;

  Window* window = new Window( this, w, h );
  SDL_Vulkan_GetDrawableSize( sdl_window, &window->pixel_width, &window->pixel_height );

  WindowFrameworkContextSDL* framework_context = new WindowFrameworkContextSDL( window, sdl_window );
  WindowRenderContextVulkan* render_context = new WindowRenderContextVulkan( window, renderer );
  window->framework_context = framework_context;
  window->render_context = render_context;

  window->id = balefire->windows.add( window );
  printf("window id:%d\n",window->id);

  if (SDL_TRUE != SDL_Vulkan_CreateSurface(
      framework_context->sdl_window,
      renderer->vulkan_instance,
      &render_context->surface
    ))
  {
    fprintf( stderr, "[ERROR] SDL_Vulkan_CreateSurface() failed.\n" );
  }

  renderer->configure_window( window );

  return window->id;
}

void FrameworkSDLVulkan::render( Window* window )
{
  window->render();
}

void FrameworkSDLVulkan::update_pixel_size( Window* window )
{
  WindowFrameworkContext* context = (WindowFrameworkContext*)window->framework_context;
  WindowFrameworkContextSDL* context_sdl = (WindowFrameworkContextSDL*)context;
  SDL_Vulkan_GetDrawableSize(
    context_sdl->sdl_window,
    &window->pixel_width, &window->pixel_height
  );
}

