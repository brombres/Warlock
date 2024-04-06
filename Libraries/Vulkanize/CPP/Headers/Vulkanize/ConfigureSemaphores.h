#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ConfigureSemaphores : Operation
  {
    Context* context;

    ConfigureSemaphores( Context* context );
    virtual bool activate();
    virtual void deactivate();

    void _create_semaphore( VkSemaphore *semaphore );
  };
};
