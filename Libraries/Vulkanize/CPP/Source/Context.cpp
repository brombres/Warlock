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

  for (auto phase : phases)
  {
    if ( !configure(phase) ) return false;
  }

  configured = true;
  return true;
}

bool Context::configure( std::string phase )
{
  Component* component = components[phase];
  if (component)
  {
    if ( !component->configure() )
    {
      return false;
    }
  }
  return true;
}

void Context::destroy()
{
  if ( !configured ) return;

  for (int i=(int)phases.size(); --i>=0; )
  {
    destroy( phases[i] );
  }
}

void Context::destroy( std::string phase )
{
  Component* component = components[ phase ];
  if (component) component->destroy();
}

void Context::add_component( std::string phase, Component* component )
{
  if (configured)
  {
    fprintf( stderr, "[Vulkanize] Error calling add_component(): components can "
                     "only be modified before configure() is called.\n" );
    return;
  }

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
  set_component( VKZ_CONFIGURE_DEVICE,       new ConfigureDevice(this,1,2) );
  set_component( VKZ_CONFIGURE_FORMATS,      new ConfigureFormats(this) );
  set_component( VKZ_CONFIGURE_SURFACE_SIZE, new ConfigureFormats(this) );
}

void Context::set_component( std::string phase, Component* component )
{
  if (configured)
  {
    fprintf( stderr, "[Vulkanize] Error calling add_component(): components can "
                     "only be modified before configure() is called.\n" );
    return;
  }

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
