#include <vector>

#include "Balefire/Balefire.h"
#include "Balefire/SDL/FrameworkSDLVulkan.h"
#include "Balefire/SDL/WindowFrameworkContextSDL.h"
#include "Balefire/Vulkan/GraphicsAPIVulkan.h"
#include "Balefire/Vulkan/WindowRendererVulkan.h"
using namespace BALEFIRE;

#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

void FrameworkSDLVulkan::configure()
{
  SDL_Init( SDL_INIT_VIDEO );
  render_api = new GraphicsAPIVulkan( this );
  render_api->configure();
}

Window* FrameworkSDLVulkan::create_window( int index, std::string name )
{
  int w = 1024;
  int h = 768;

  int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE;
  flags |= SDL_WINDOW_ALLOW_HIGHDPI;

  SDL_Window* sdl_window =
    SDL_CreateWindow(
      name.c_str(),
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      w,
      h,
      flags
    );

  SDL_RaiseWindow( sdl_window );

  //unsigned int extensionCount = 0;
  //SDL_Vulkan_GetInstanceExtensions(sdl_window, &extensionCount, nullptr);
  //std::vector<const char *> extensionNames(extensionCount);
  //SDL_Vulkan_GetInstanceExtensions(sdl_window, &extensionCount, extensionNames.data());
  //printf("SDL REQUIRED VULKAN INSTANCE EXTENSIONS:%d\n",extensionCount);
  //for (int i=0; i<extensionCount; ++i)
  //{
  //  printf( "%d %s\n",i,extensionNames[i] );
  //}


  GraphicsAPIVulkan* render_api = (GraphicsAPIVulkan*)this->render_api;

  Window* window = new Window( this, index, w, h );
  SDL_Vulkan_GetDrawableSize( sdl_window, &window->pixel_width, &window->pixel_height );

  WindowFrameworkContextSDL* framework_context = new WindowFrameworkContextSDL( window, sdl_window );
  WindowRendererVulkan* renderer = new WindowRendererVulkan( window, render_api );
  window->framework_context = framework_context;
  window->renderer = renderer;

  if (balefire->windows.size() <= index) balefire->windows.resize( index+1 );
  balefire->windows[index] = window;
  printf("Created window %d\n", window->index);

  VkSurfaceKHR surface;
  if (SDL_TRUE != SDL_Vulkan_CreateSurface(
      framework_context->sdl_window,
      Vulkanize::instance->vulkan_instance,
      &surface
    ))
  {
    fprintf( stderr, "[ERROR] SDL_Vulkan_CreateSurface() failed.\n" );
  }

  renderer->surface = surface;
  renderer->configure( surface );

  render_api->configure_window( window );

  return window;
}

void FrameworkSDLVulkan::render( Window* window, unsigned char* render_data, int count )
{
  window->render( render_data, count );
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

