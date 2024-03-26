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

  for (int i=(int)configuration_phases.size(); --i>=0; )
  {
    Procedure* procedure = procedures[ configuration_phases[i] ];
    if (procedure) delete procedure;
  }
  procedures.clear();

  vkb::destroy_surface( vulkanize.vulkan_instance, surface );
  surface = nullptr;
}

bool Context::configure()
{
  if ( !configuration_phases.size() ) configure_procedures();

  for (auto phase : configuration_phases)
  {
    if ( !configure(phase) ) return false;
  }

  configured = true;
  return true;
}

bool Context::configure( std::string phase )
{
  Procedure* procedure = procedures[phase];
  if (procedure)
  {
    if ( !procedure->configure() )
    {
      return false;
    }
  }
  return true;
}

bool Context::render( std::string phase )
{
  Procedure* procedure = procedures[phase];
  if (procedure)
  {
    if ( !procedure->configure() )
    {
      return false;
    }
  }
  return true;
}

void Context::destroy()
{
  if ( !configured ) return;

  for (int i=(int)configuration_phases.size(); --i>=0; )
  {
    destroy( configuration_phases[i] );
  }
}

void Context::destroy( std::string phase )
{
  Procedure* procedure = procedures[phase];
  if (procedure) procedure->destroy();
}

void Context::add_configuration_phase( std::string phase, Procedure* procedure )
{
  if (configured)
  {
    fprintf( stderr, "[Vulkanize] Error calling add_configuration_phase(): procedures can "
                     "only be modified before configure() is called.\n" );
    return;
  }

  Procedure* existing = procedures[phase];
  if (existing)
  {
    existing->add_sibling( procedure );
  }
  else
  {
    // This config phase does not yet exist in the configuration_phases definition.
    configuration_phases.push_back( phase );

    procedures[phase] = procedure;
  }
}

void Context::add_render_phase( std::string phase, Procedure* procedure )
{
  Procedure* existing = procedures[phase];
  if (existing) existing->add_sibling( procedure );
  else          procedures[phase] = procedure;
}

void Context::configure_procedures()
{
  set_configuration_phase( VKZ_CONFIGURE_DEVICE,       new ConfigureDevice(this,1,2) );
  set_configuration_phase( VKZ_CONFIGURE_FORMATS,      new ConfigureFormats(this) );
  set_configuration_phase( VKZ_CONFIGURE_SURFACE_SIZE, new ConfigureSurfaceSize(this) );
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

  for (int i=(int)configuration_phases.size(); --i>=0; ) destroy( configuration_phases[i] );

  for (auto phase : configuration_phases) configure( phase );
}

void Context::set_configuration_phase( std::string phase, Procedure* procedure )
{
  if (configured)
  {
    fprintf( stderr, "[Vulkanize] Error calling add_configuration_phase(): procedures can "
                     "only be modified before configure() is called.\n" );
    return;
  }

  Procedure* existing = procedures[phase];
  if (existing)
  {
    delete existing;
  }
  else
  {
    // This config phase does not yet exist in the configuration_phases definition.
    configuration_phases.push_back( phase );
  }
  procedures[phase] = procedure;
}

void Context::set_render_phase( std::string phase, Procedure* procedure )
{
  Procedure* existing = procedures[phase];
  if (existing)
  {
    existing->destroy();
    delete existing;
  }
  procedures[phase] = procedure;
}
