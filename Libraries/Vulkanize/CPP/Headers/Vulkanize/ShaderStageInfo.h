#pragma once

#include <string>
#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ShaderStageInfo
  {
    VkShaderStageFlagBits stage;
    VkShaderModule        module;
    std::string           main_function_name;

    ShaderStageInfo( VkShaderStageFlagBits stage, VkShaderModule module )
      : stage(stage), module(module), main_function_name("main") {}

    ShaderStageInfo( VkShaderStageFlagBits stage, VkShaderModule module, std::string main_function_name )
      : stage(stage), module(module), main_function_name(main_function_name) {}
  };
};
