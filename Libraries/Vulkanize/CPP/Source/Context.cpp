#include <cstdio>

#include "VkBootstrap.h"

#include "Vulkanize/Vulkanize.h"
#include "Vulkanize/Context.h"
#include "Vulkanize/ConfigureDevice.h"
using namespace VULKANIZE;

Context::Context( VkSurfaceKHR surface ) : surface(surface)
{
}

Context::~Context()
{
  destroy();

  for (int i=(int)process.size(); --i>=0; )
  {
    Component* component = components[ process[i] ];
    if (component) delete component;
  }
  components.clear();

  vkb::destroy_surface( vulkanize.vulkan_instance, surface );
  surface = nullptr;
}

bool Context::configure()
{
  configure_components();

  bool error = false;
  for (auto step : process)
  {
    Component* component = components[step];
    if (component)
    {
      if ( !component->configure() )
      {
        error = true;
        break;
      }
    }
  }
  if (error) return false;

  configured = true;
  return true;
}

bool Context::destroy()
{
  return false;
}

void Context::add_component( std::string step_name, Component* component )
{
  if (configured)
  {
    fprintf( stderr, "[Vulkanize] Error calling add_component(): components can "
                     "only be modified before configure() is called.\n" );
    return;
  }

  Component* existing = components[step_name];
  if (existing)
  {
    existing->add_sibling( component );
  }
  else
  {
    // This config step does not yet exist in the process definition.
    process.push_back( step_name );

    components[step_name] = component;
  }
}

void Context::configure_components()
{
  set_component( VKZ_CONFIGURE_DEVICE, new ConfigureDevice(this) );
}

void Context::set_component( std::string step_name, Component* component )
{
  if (configured)
  {
    fprintf( stderr, "[Vulkanize] Error calling add_component(): components can "
                     "only be modified before configure() is called.\n" );
    return;
  }

  Component* existing = components[step_name];
  if (existing)
  {
    delete existing;
  }
  else
  {
    // This config step does not yet exist in the process definition.
    process.push_back( step_name );
  }
  components[step_name] = component;
}
