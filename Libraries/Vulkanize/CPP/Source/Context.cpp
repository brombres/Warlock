#include <cstdio>

#include "VkBootstrap.h"

#include "Vulkanize/Vulkanize.h"
#include "Vulkanize/Context.h"
#include "Vulkanize/ConfigureDevice.h"
using namespace VKZ;
using namespace std;

Context::Context( VkSurfaceKHR surface ) : surface(surface)
{
}

Context::~Context()
{
  destroy();

  for (auto phase : phases)
  {
    Operation* operation = operations[phase];
    if (operation) delete operation;
  }
  phases.clear();
  operations.clear();

  vkb::destroy_surface( vulkanize.vulkan_instance, surface );
  surface = nullptr;
}

void Context::add_operation( string phase, Operation* operation )
{
  Operation* existing = operations[phase];
  if (existing)
  {
    existing->add_sibling( operation );
  }
  else
  {
    // This phase does not yet exist.
    phases.push_back( phase );
  }
  operations[phase] = operation;
}

bool Context::activate( string phase )
{
  if ( !dispatch_event(phase, "activate") ) return false;
  return true;
}

bool Context::configure()
{
  if (configured) return true;
  if ( !operations.size() ) configure_operations();
  if ( !activate("configure") ) return false;
  configured = true;
  return true;
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
  set_operation( "configure.graphics_pipeline",         new ConfigureGraphicsPipeline(this) );
  set_operation( "configure.swapchain.framebuffers",    new ConfigureFramebuffers(this) );
  set_operation( "configure.swapchain.command_pool",    new ConfigureCommandPool(this) );
  set_operation( "configure.swapchain.command_buffers", new ConfigureCommandBuffers(this) );
  set_operation( "configure.semaphores",                new ConfigureSemaphores(this) );
  set_operation( "configure.fences",                    new ConfigureFences(this) );
}

void Context::deactivate( string phase )
{
  dispatch_event( phase, "deactivate", true );
}

void Context::destroy()
{
  device_dispatch.deviceWaitIdle();
  deactivate( "configure" );
  configured = false;
}

bool Context::dispatch_event( string phase, string event, bool reverse_order )
{
  if (reverse_order)
  {
    for (int i=(int)phases.size(); --i>=0; )
    {
      string cur_phase = phases[i];
      if (_phase_begins_with(cur_phase,phase))
      {
        Operation* operation = operations[ cur_phase ];
        if (operation && !operation->handle_event(event,true)) return false;
      }
    }
    return true;
  }
  else
  {
    for (auto cur_phase : phases)
    {
      if (_phase_begins_with(cur_phase,phase))
      {
        Operation* operation = operations[ cur_phase ];
        if (operation && !operation->handle_event(event,false)) return false;
      }
    }
    return true;
  }
}

bool Context::execute( string phase )
{
  return dispatch_event( phase, "execute" );
}

int Context::find_memory_type( uint32_t typeFilter, VkMemoryPropertyFlags properties )
{
  VkPhysicalDeviceMemoryProperties memory_properties;
  vulkanize.instance_dispatch.getPhysicalDeviceMemoryProperties( physical_device, &memory_properties );

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

void Context::set_operation( string phase, Operation* operation )
{
  Operation* existing = operations[phase];
  if (existing)
  {
    delete existing;
  }
  else
  {
    // This phase does not yet exist in 'phases'.
    phases.push_back( phase );
  }
  operations[phase] = operation;
}

bool Context::_phase_begins_with( const string& phase, const string& other )
{
  auto value_n = phase.size();
  auto n = other.size();
  if (value_n < n) return false;

  if (0 != phase.compare(0,n,other)) return false;
  if (value_n == n) return true;
  return (phase[n] == '.');
}
