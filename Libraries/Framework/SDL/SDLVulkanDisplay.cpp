#include "SDLVulkanDisplay.h"
#include "VulkanRenderer.h"
using namespace Warlock;

SDLVulkanDisplay::~SDLVulkanDisplay()
{
  if (renderer)
  {
    delete renderer;
    renderer = nullptr;
  }
}

void SDLVulkanDisplay::configure()
{
  renderer = new VulkanRenderer();
  SDL_Init( SDL_INIT_VIDEO );
}

SDL_WindowFlags SDLVulkanDisplay::window_creation_flags()
{
  return (SDL_WindowFlags)(SDLDisplay::window_creation_flags() | SDL_WINDOW_VULKAN);
}
