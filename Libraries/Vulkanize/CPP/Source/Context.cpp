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

void Context::add_event_handler( std::string phase, Action* action )
{
  Action* existing = actions[phase];
  if (existing) existing->add_sibling( action );
  else          actions[phase] = action;
}

bool Context::configure()
{
  if ( !configuration_phases.size() ) configure_actions();
  if ( !dispatch_configuration_event(VKZ_EVENT_CONFIGURE) ) return false;
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
  dispatch_configuration_event( VKZ_EVENT_DEACTIVATE, true );
  configured = false;
}

void Context::deactivate( std::string phase )
{
  Action* action = actions[phase];
  if (action) action->deactivate();
}

bool Context::dispatch_configuration_event( int event_type, bool reverse_order )
{
  if (reverse_order)
  {
    for (int i=(int)configuration_phases.size(); --i>=0; )
    {
      if ( !dispatch_event(configuration_phases[i],event_type) ) return false;
    }
    return true;
  }
  else
  {
    for (auto phase : configuration_phases)
    {
      if ( !dispatch_event(phase,event_type) ) return false;
    }
    return true;
  }
}

bool Context::dispatch_event( std::string phase )
{
  Action* action = actions[phase];
  if (action)
  {
    if ( !action->execute() ) return false;
  }
  return true;
}

bool Context::dispatch_event( std::string phase, int event_type )
{
  Action* action = actions[phase];
  if (action)
  {
    if ( !action->handle_event(event_type) ) return false;
  }
  return true;
}

bool Context::execute( std::string phase )
{
  return dispatch_event( phase, VKZ_EVENT_EXECUTE );
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

  dispatch_configuration_event( VKZ_EVENT_SURFACE_LOST, true );
  //for (int i=(int)configuration_phases.size(); --i>=0; ) deactivate( configuration_phases[i] );

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

void Context::set_event_handler( std::string phase, Action* action )
{
  Action* existing = actions[phase];
  if (existing)
  {
    existing->deactivate();
    delete existing;
  }
  actions[phase] = action;
}
