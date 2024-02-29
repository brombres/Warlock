#include "SDLVulkanRenderer.h"
#include "VulkanRenderer.h"
using namespace Warlock;

SDLVulkanRenderer::SDLVulkanRenderer( SDLVulkanFramework* framework )
  : framework(framework) {}

void SDLVulkanRenderer::configure_window( Window window )
{
  //SDL_Vulkan_CreateSurface( windows[window], instance, &surface);
}

