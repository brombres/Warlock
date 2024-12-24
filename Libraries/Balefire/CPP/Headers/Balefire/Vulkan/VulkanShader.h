#pragma once

#include "Balefire/Vulkan/GraphicsAPIVulkan.h"

namespace BALEFIRE
{
  struct VulkanShader : Shader
  {
    VKZ::Ref<VKZ::Shader> vkz_shader;

    VulkanShader( VulkanContext* context, ShaderStage stage, std::string filename, std::string source,
                  std::string main_function_name="main" );
    VulkanShader( VulkanContext* context, ShaderStage stage, std::string filename,
                  const char* spirv_bytecode, size_t byte_count,
                  std::string main_function_name="main" );

    virtual ~VulkanShader();
  };
};
