#include "SDLVulkanFramework.h"
#include "SDLVulkanRenderer.h"
using namespace Warlock;

SDLVulkanFramework::~SDLVulkanFramework()
{
  if (renderer)
  {
    delete renderer;
    renderer = nullptr;
  }
}

void SDLVulkanFramework::configure()
{
  SDL_Init( SDL_INIT_VIDEO );
  //int error = SDL_Vulkan_LoadLibrary( NULL );
  //printf("LOAD ERROR: %d\n",error);
  renderer = new SDLVulkanRenderer( this );
  renderer->configure();
}

SDL_WindowFlags SDLVulkanFramework::window_creation_flags()
{
  return (SDL_WindowFlags)(SDLFramework::window_creation_flags() | SDL_WINDOW_VULKAN);
}
