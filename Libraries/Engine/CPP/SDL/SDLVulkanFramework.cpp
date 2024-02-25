#include "SDLVulkanFramework.h"
#include "VulkanRenderer.h"
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
  renderer = new VulkanRenderer();
  SDL_Init( SDL_INIT_VIDEO );
}

SDL_WindowFlags SDLVulkanFramework::window_creation_flags()
{
  return (SDL_WindowFlags)(SDLFramework::window_creation_flags() | SDL_WINDOW_VULKAN);
}
