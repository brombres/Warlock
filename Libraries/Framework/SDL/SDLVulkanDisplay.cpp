#include "SDLVulkanDisplay.h"
#include "VulkanRenderer.h"

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
}
