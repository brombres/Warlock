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
  deactivate();

  for (int i=(int)configuration_phases.size(); --i>=0; )
  {
    Action* action = actions[ configuration_phases[i] ];
    if (action) delete action;
  }
  actions.clear();

  vkb::destroy_surface( vulkanize.vulkan_instance, surface );
  surface = nullptr;
}

void Context::add_configuration_action( std::string phase, Action* action )
{
  if (configured)
  {
    fprintf( stderr, "[Vulkanize] Error calling add_configuration_action(): actions can "
                     "only be modified before configure() is called.\n" );
    return;
  }

  Action* existing = actions[phase];
  if (existing)
  {
    existing->add_sibling( action );
  }
  else
  {
    // This config phase does not yet exist in the configuration_phases definition.
    configuration_phases.push_back( phase );
    actions[phase] = action;
  }
}

void Context::add_event_handler( std::string event, Action* action )
{
  Action* existing = actions[event];
  if (existing) existing->add_sibling( action );
  else          actions[event] = action;
}

bool Context::configure()
{
  if ( !configuration_phases.size() ) configure_actions();

  for (auto phase : configuration_phases)
  {
    if ( !dispatch_event(phase) ) return false;
  }

  configured = true;
  return true;
}

void Context::configure_actions()
{
  set_configuration_action( VKZ_CONFIGURE_DEVICE,       new ConfigureDevice(this,1,2) );
  set_configuration_action( VKZ_CONFIGURE_FORMATS,      new ConfigureFormats(this) );
  set_configuration_action( VKZ_CONFIGURE_SURFACE_SIZE, new ConfigureSurfaceSize(this) );
  set_configuration_action( VKZ_CONFIGURE_SWAPCHAIN,    new ConfigureSwapchain(this) );
}

void Context::deactivate()
{
  if ( !configured ) return;

  for (int i=(int)configuration_phases.size(); --i>=0; )
  {
    deactivate( configuration_phases[i] );
  }
}

void Context::deactivate( std::string event )
{
  Action* action = actions[event];
  if (action) action->deactivate();
}

bool Context::dispatch_event( std::string event )
{
  Action* action = actions[event];
  if (action)
  {
    if ( !action->execute() ) return false;
  }
  return true;
}

void Context::recreate_swapchain()
{
  std::vector<std::string> configuration_phases;
  configuration_phases.push_back( VKZ_CONFIGURE_SURFACE_SIZE );
  configuration_phases.push_back( VKZ_CONFIGURE_SWAPCHAIN );
  configuration_phases.push_back( VKZ_CONFIGURE_DEPTH_STENCIL );
  configuration_phases.push_back( VKZ_CONFIGURE_FRAMEBUFFERS );
  configuration_phases.push_back( VKZ_CONFIGURE_COMMAND_POOL );
  configuration_phases.push_back( VKZ_CONFIGURE_COMMAND_BUFFERS );

  for (int i=(int)configuration_phases.size(); --i>=0; ) deactivate( configuration_phases[i] );

  for (auto phase : configuration_phases) dispatch_event( phase );
}

void Context::set_configuration_action( std::string phase, Action* action )
{
  if (configured)
  {
    fprintf( stderr, "[Vulkanize] Error calling set_configuration_action(): actions can "
                     "only be modified before configure() is called.\n" );
    return;
  }

  Action* existing = actions[phase];
  if (existing)
  {
    delete existing;
  }
  else
  {
    // This config phase does not yet exist in the configuration_phases definition.
    configuration_phases.push_back( phase );
  }
  actions[phase] = action;
}

void Context::set_event_handler( std::string event, Action* action )
{
  Action* existing = actions[event];
  if (existing)
  {
    existing->deactivate();
    delete existing;
  }
  actions[event] = action;
}
