#include "Balefire/Vulkan/WindowRendererVulkan.h"
using namespace BALEFIRE;

using namespace glm;
using namespace std;

#include "Vulkanize/Vulkanize.h"
#include "Vulkanize/Context.h"
using namespace VKZ;

VulkanShader::VulkanShader( VulkanContext* context, ShaderStage stage, string filename,
    string source, string main_function_name ) : Shader(stage)
{
  vkz_shader = new VKZ::Shader(
    context,
    (VkShaderStageFlagBits)stage,
    filename,
    source,
    main_function_name
  );
}

VulkanShader::VulkanShader( VulkanContext* context, ShaderStage stage, string filename,
    const char* spirv_bytecode, size_t byte_count, string main_function_name ) : Shader(stage)
{
  vkz_shader = new VKZ::Shader(
    context,
    (VkShaderStageFlagBits)stage,
    filename,
    (char*)spirv_bytecode,
    byte_count,
    main_function_name
  );
}

VulkanShader::~VulkanShader()
{
  vkz_shader = nullptr;
}
