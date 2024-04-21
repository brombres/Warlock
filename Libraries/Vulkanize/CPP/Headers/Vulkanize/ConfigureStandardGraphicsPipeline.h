#pragma once

#include <vector>
#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ConfigureStandardGraphicsPipeline : ConfigureGraphicsPipeline
  {
    ConfigureStandardGraphicsPipeline( Context* context );

    virtual bool activate();
    virtual void deactivate();
  };
};
