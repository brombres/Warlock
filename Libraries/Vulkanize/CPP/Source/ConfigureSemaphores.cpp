#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

ConfigureSemaphores::ConfigureSemaphores( Context* context ) : context(context)
{
}

bool ConfigureSemaphores::activate()
{
  _create_semaphore( &context->image_available_semaphore );
  _create_semaphore( &context->rendering_finished_semaphore );
  return true;
}

void ConfigureSemaphores::deactivate()
{
  context->device_dispatch.destroySemaphore( context->image_available_semaphore, nullptr );
  context->device_dispatch.destroySemaphore( context->rendering_finished_semaphore, nullptr );
}

void ConfigureSemaphores::_create_semaphore( VkSemaphore *semaphore )
{
  VkSemaphoreCreateInfo semaphore_info = {};
  semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  context->device_dispatch.createSemaphore( &semaphore_info, nullptr, semaphore );
}
