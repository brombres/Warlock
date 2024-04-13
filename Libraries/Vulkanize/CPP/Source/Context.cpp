#include <cstdio>

#include "VkBootstrap.h"

#include "Vulkanize/Vulkanize.h"
#include "Vulkanize/Context.h"
#include "Vulkanize/ConfigureDevice.h"
using namespace VKZ;
using namespace std;

#include "glslang/Include/glslang_c_interface.h"

// Required for use of glslang_default_resource
#include <glslang/Public/resource_limits_c.h>


Context::Context( VkSurfaceKHR surface ) : surface(surface)
{
  if ( !Vulkanize::instance )
  {
    VKZ_LOG_ERROR( "Error creating Context - a Vulkanize instance must be created before creating a Context.\n" );
    exit(1);
  }

  Vulkanize::instance->context_instances.push_back( this );
}

Context::~Context()
{
  if (Vulkanize::instance)
  {
    vector<Context*>& instances = Vulkanize::instance->context_instances;
    for (auto it=instances.begin(); it!=instances.end(); ++it)
    {
      if (*it == this)
      {
        instances.erase( it );
        break;
      }
    }
  }

  destroy();

  vkb::destroy_surface( Vulkanize::instance->vulkan_instance, surface );
  surface = nullptr;
}

VkShaderModule Context::compile_shader( VKZ::Shader type, const string& filename, const string& shader_source )
{
  glslang_stage_t stage;
  switch (type)
  {
    case VKZ::Shader::FRAGMENT: stage = GLSLANG_STAGE_FRAGMENT; break;
    case VKZ::Shader::VERTEX:   stage = GLSLANG_STAGE_VERTEX; break;
    default:
      VKZ_LOG_ERROR( "[Vulkanize] Internal error: unhandled VKZ::Shader type in Context::compile_shader().\n" );
  }
  auto spirv = compile_shader_to_spirv( stage, filename.c_str(), shader_source.c_str() );
  if (spirv.size == 0) return VK_NULL_HANDLE;

  VkShaderModuleCreateInfo create_info = {};
  create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  create_info.codeSize = spirv.size;
  create_info.pCode = (const uint32_t*)spirv.code;

  VkShaderModule shader_module;
  VKZ_ON_ERROR(
    "creating shader module",
    device_dispatch.createShaderModule( &create_info, nullptr, &shader_module ),
    free(spirv.code); return VK_NULL_HANDLE;
  );

  free( spirv.code );
  return shader_module;
}

SPIRVBinary Context::compile_shader_to_spirv( int stage, const char* filename, const char* shader_source)
{
  const glslang_input_t input = {
    .language = GLSLANG_SOURCE_GLSL,
    .stage = (glslang_stage_t)stage,
    .client = GLSLANG_CLIENT_VULKAN,
    .client_version = GLSLANG_TARGET_VULKAN_1_2,
    .target_language = GLSLANG_TARGET_SPV,
    .target_language_version = GLSLANG_TARGET_SPV_1_5,
    .code = shader_source,
    .default_version = 100,
    .default_profile = GLSLANG_NO_PROFILE,
    .force_default_version_and_profile = false,
    .forward_compatible = false,
    .messages = GLSLANG_MSG_DEFAULT_BIT,
    .resource = glslang_default_resource(),
  };

  glslang_shader_t* shader = glslang_shader_create(&input);

  SPIRVBinary bin =
  {
    .size = 0,
    .code = NULL,
  };

  if (!glslang_shader_preprocess(shader, &input))	{
    VKZ_LOG_ERROR( "[Vulkanize] Preprocessing error compiling shader '%s'.\n", filename );
    VKZ_LOG_ERROR( "%s\n", glslang_shader_get_info_log(shader) );
    VKZ_LOG_ERROR( "%s\n", glslang_shader_get_info_debug_log(shader) );
    VKZ_LOG_ERROR( "%s\n", input.code );
    glslang_shader_delete( shader );
    return bin;
  }

  if (!glslang_shader_parse(shader, &input))
  {
    VKZ_LOG_ERROR( "[Vulkanize] Parse error compiling shader '%s'.\n", filename );
    VKZ_LOG_ERROR( "%s\n", glslang_shader_get_info_log(shader) );
    VKZ_LOG_ERROR( "%s\n", glslang_shader_get_info_debug_log(shader) );
    VKZ_LOG_ERROR( "%s\n", glslang_shader_get_preprocessed_code(shader) );
    glslang_shader_delete( shader );
    return bin;
  }

  glslang_program_t* program = glslang_program_create();
  glslang_program_add_shader(program, shader);

  if (!glslang_program_link(program, GLSLANG_MSG_SPV_RULES_BIT | GLSLANG_MSG_VULKAN_RULES_BIT))
  {
    VKZ_LOG_ERROR( "[Vulkanize] Link error compiling shader '%s'.\n", filename );
    VKZ_LOG_ERROR( "%s\n", glslang_program_get_info_log(program) );
    VKZ_LOG_ERROR( "%s\n", glslang_program_get_info_debug_log(program) );
    glslang_program_delete( program );
    glslang_shader_delete( shader );
    return bin;
  }

  glslang_program_SPIRV_generate( program, (glslang_stage_t)stage );

  bin.size = glslang_program_SPIRV_get_size(program) * sizeof(uint32_t);
  bin.code = (uint32_t*) malloc( bin.size );
  glslang_program_SPIRV_get( program, bin.code );

  const char* spirv_messages = glslang_program_SPIRV_get_messages(program);
  if (spirv_messages) printf("(%s) %s\b", filename, spirv_messages);

  glslang_program_delete( program );
  glslang_shader_delete( shader );

  return bin;
}

void Context::configure_operations()
{
  set_operation( "configure.device",                    new ConfigureDevice(this,1,2) );
  set_operation( "configure.formats",                   new ConfigureFormats(this) );
  set_operation( "configure.swapchain.surface_size",    new ConfigureSurfaceSize(this) );
  set_operation( "configure.swapchain",                 new ConfigureSwapchain(this) );
  set_operation( "configure.swapchain.depth_stencil",   new ConfigureDepthStencil(this) );
  set_operation( "configure.queues",                    new ConfigureQueues(this) );
  set_operation( "configure.render_passes",             new ConfigureRenderPasses(this) );
  set_operation( "configure.shaders",                   new ConfigureShaders(this) );
  set_operation( "configure.graphics_pipeline",         new ConfigureGraphicsPipeline(this) );
  set_operation( "configure.swapchain.framebuffers",    new ConfigureFramebuffers(this) );
  set_operation( "configure.swapchain.command_pool",    new ConfigureCommandPool(this) );
  set_operation( "configure.swapchain.command_buffers", new ConfigureCommandBuffers(this) );
  set_operation( "configure.semaphores",                new ConfigureSemaphores(this) );
  set_operation( "configure.fences",                    new ConfigureFences(this) );
  set_operation( "render.begin",                        new RenderBegin(this) );
  set_operation( "render.end",                          new RenderEnd(this) );
}

void Context::destroy()
{
  device_dispatch.deviceWaitIdle();
  OperationManager::destroy();
}

int Context::find_memory_type( uint32_t typeFilter, VkMemoryPropertyFlags properties )
{
  VkPhysicalDeviceMemoryProperties memory_properties;
  Vulkanize::instance->instance_dispatch.getPhysicalDeviceMemoryProperties( physical_device, &memory_properties );

  for (uint32_t i=0; i<memory_properties.memoryTypeCount; ++i)
  {
    if ( (typeFilter & (1 << i)) &&
        (memory_properties.memoryTypes[i].propertyFlags & properties) == properties)
    {
      return i;
    }
  }

  return -1;
}

void Context::recreate_swapchain()
{
  device_dispatch.deviceWaitIdle();
  dispatch_event( "configure.swapchain", "surface_lost", true );
  deactivate( "configure.swapchain" );
  activate( "configure.swapchain" );
}

