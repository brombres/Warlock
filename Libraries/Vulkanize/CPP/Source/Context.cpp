#include "VkBootstrap.h"

#include "Vulkanize/Vulkanize.h"
#include "Vulkanize/Context.h"
#include "Vulkanize/StandardConfigureDeviceComponent.h"
using namespace VULKANIZE;

Context::Context( VkSurfaceKHR surface ) : surface(surface)
{
}

Context::~Context()
{
  destroy();

  for (int i=(int)process.size(); --i>=0; )
  {
    auto& list = components[process[i]];
    while (list.size())
    {
      Component* component = list.back();
      list.pop_back();
      delete component;
    }
  }

  vkb::destroy_surface( vulkanize.vulkan_instance, surface );
  surface = nullptr;
}

bool Context::configure()
{
  configure_process();
  configure_components();

  for (auto step : process)
  {
    auto list = components[step];
    for (auto component : list)
    {
      component->configure();
    }
  }

  _configure_device();
  configured = true;
  return true;
}

bool Context::_configure_device()
{
  return true;
}

bool Context::destroy()
{
  return false;
}

void Context::add_component( std::string step_name, Component* component )
{
  components[step_name].push_back( component );
}

void Context::configure_components()
{
  set_component( VKZ_CONFIGURE_DEVICE, new StandardConfigureDeviceComponent(this) );
}

void Context::configure_process()
{
  process.clear();
  process.push_back( VKZ_CONFIGURE_DEVICE );
  process.push_back( VKZ_CONFIGURE_SWAPCHAIN );
  process.push_back( VKZ_CONFIGURE_QUEUES );
  process.push_back( VKZ_CONFIGURE_DEPTH_STENCIL );
  process.push_back( VKZ_CONFIGURE_RENDER_PASS );
  process.push_back( VKZ_CONFIGURE_GRAPHICS_PIPELINES );
  process.push_back( VKZ_CONFIGURE_FRAMEBUFFERS );
  process.push_back( VKZ_CONFIGURE_COMMAND_POOL );
  process.push_back( VKZ_CONFIGURE_COMMAND_BUFFERS );
  process.push_back( VKZ_CONFIGURE_SEMAPHORES );
  process.push_back( VKZ_CONFIGURE_FENCES );
}

void Context::set_component( std::string step_name, Component* component )
{
  std::vector<Component*>& list = components[step_name];
  while (list.size())
  {
    delete list.back();
    list.pop_back();
  }
  list.push_back( component );
}
