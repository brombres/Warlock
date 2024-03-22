#include "VkBootstrap.h"

#include "Vulkanize/Vulkanize.h"
#include "Vulkanize/Context.h"
using namespace VULKANIZE;

Context::~Context()
{
  vkb::destroy_surface( vulkanize.vulkan_instance, surface );
  surface = nullptr;
}
