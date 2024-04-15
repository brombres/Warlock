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

