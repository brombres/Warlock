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
}
