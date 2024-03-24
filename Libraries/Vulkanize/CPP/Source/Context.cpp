#include <cstdio>

#include "VkBootstrap.h"

#include "Vulkanize/Vulkanize.h"
#include "Vulkanize/Context.h"
#include "Vulkanize/ConfigureDevice.h"
using namespace VKZ;

Context::Context( VkSurfaceKHR surface ) : surface(surface)
{
}

Context::~Context()
{
  destroy();

  for (int i=(int)phases.size(); --i>=0; )
  {
    Component* component = components[ phases[i] ];
    if (component) delete component;
  }
  components.clear();

  vkb::destroy_surface( vulkanize.vulkan_instance, surface );
  surface = nullptr;
}

bool Context::configure()
{
  if ( !phases.size() ) configure_components();

  bool error = false;
  for (auto phase : phases)
  {
    Component* component = components[phase];
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

void Context::add_component( Component* component )
{
  if (configured)
  {
    fprintf( stderr, "[Vulkanize] Error calling add_component(): components can "
                     "only be modified before configure() is called.\n" );
    return;
  }

  const char* phase = component->phase();
  Component* existing = components[phase];
  if (existing)
  {
    existing->add_sibling( component );
  }
  else
  {
    // This config phase does not yet exist in the phases definition.
    phases.push_back( phase );

    components[phase] = component;
  }
}

void Context::configure_components()
{
  set_component( new ConfigureDevice(this,1,2) );
}

void Context::set_component( Component* component )
{
  if (configured)
  {
    fprintf( stderr, "[Vulkanize] Error calling add_component(): components can "
                     "only be modified before configure() is called.\n" );
    return;
  }

  const char* phase = component->phase();
  Component* existing = components[phase];
  if (existing)
  {
    delete existing;
  }
  else
  {
    // This config phase does not yet exist in the phases definition.
    phases.push_back( phase );
  }
  components[phase] = component;
}
