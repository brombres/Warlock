#include "SDLVulkanDisplayManager.h"
#include "VulkanRenderer.h"

SDLVulkanDisplayManager::~SDLVulkanDisplayManager()
{
  if (renderer)
  {
    delete renderer;
    renderer = nullptr;
  }
}

void SDLVulkanDisplayManager::configure()
{
  renderer = new VulkanRenderer();
}
