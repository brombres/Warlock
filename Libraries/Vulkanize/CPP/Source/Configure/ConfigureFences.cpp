#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

bool ConfigureFences::activate()
{
  context->fences.resize( context->swapchain_count );
  for (uint32_t i=0; i<context->swapchain_count; ++i)
  {
    VkFenceCreateInfo fence_info = {};
    fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    VKZ_REQUIRE(
      "creating fence",
      context->device_dispatch.createFence( &fence_info, nullptr, &context->fences[i] )
    );
  }
  return true;
}

void ConfigureFences::deactivate()
{
  for (auto fence : context->fences)
  {
    context->device_dispatch.destroyFence( fence, nullptr );
  }
}

