#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

ConfigureCommandBuffers::ConfigureCommandBuffers( Context* context ) : context(context)
{
}

bool ConfigureCommandBuffers::activate()
{
  VkCommandBufferAllocateInfo allocateInfo = {};
  allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocateInfo.commandPool = context->command_pool;
  allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocateInfo.commandBufferCount = (uint32_t)context->swapchain_images.size();

  context->command_buffers.resize( context->swapchain_images.size() );
  context->device_dispatch.allocateCommandBuffers( &allocateInfo, context->command_buffers.data() );
  return true;
}

void ConfigureCommandBuffers::deactivate()
{
  context->device_dispatch.freeCommandBuffers(
    context->command_pool,
    (uint32_t)context->command_buffers.size(),
    context->command_buffers.data()
  );
}

