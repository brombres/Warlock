#include <cstdio>

#include "VkBootstrap.h"

#include "Vulkanize/Vulkanize.h"
#include "Vulkanize/Context.h"
#include "Vulkanize/ConfigureDevice.h"
using namespace VKZ;
using namespace std;

struct TaskPhase
{
  string task;
  string phase;

  TaskPhase( string task, string phase ) : task(task), phase(phase) {}

  TaskPhase( string task_phase )
  {
    auto i = task_phase.find( '.' );
    if (i == string::npos)
    {
      task = task_phase;
      phase = "*";
    }
    else
    {
      task = task_phase;
      task.resize( i );
      phase = task_phase.c_str() + i + 1;
    }
  }
};

Context::Context( VkSurfaceKHR surface ) : surface(surface)
{
}

Context::~Context()
{
  deactivate();

  for (int i=(int)configuration_phases.size(); --i>=0; )
  {
    Operation* operation = operations[ configuration_phases[i] ];
    if (operation) delete operation;
  }
  operations.clear();

  vkb::destroy_surface( vulkanize.vulkan_instance, surface );
  surface = nullptr;
}

void Context::add_operation( string task, Operation* operation )
{
  Operation* existing = operations[task];
  if (existing)
  {
    existing->add_sibling( operation );
  }
  else
  {
    // This task.phase does not yet exist in task_phases.
    TaskPhase task_phase( task );
    task_phases[ task_phase.task ].push_back( task_phase.phase );
  }
  operations[task] = operation;
}

bool Context::configure()
{
  if ( !operations.size() ) configure_operations();

  if (task_phases.find("configure") == task_phases.end()) return true;

  vector<string>& phases = task_phases["configure"];
  for (auto phase : phases)
  {
    Operation* operation = operations[ phase ];
    if (operation && !operation->configure())
    {
      return false;
    }
  }

  configured = true;
  return true;
}

void Context::configure_operations()
{
  set_operation( "configure.device",       new ConfigureDevice(this,1,2) );
  set_operation( "configure.formats",      new ConfigureFormats(this) );
  set_operation( "configure.surface_size", new ConfigureSurfaceSize(this) );
  set_operation( "configure.swapchain",    new ConfigureSwapchain(this) );
}

void Context::deactivate()
{
  if ( !configured ) return;
  if (task_phases.find("configure") == task_phases.end()) return;

  vector<string>& phases = task_phases["configure"];
  for (int i=(int)phases.size(); --i>=0; )
  {
    Operation* operation = operations[ phases[i] ];
    if (operation) operation->deactivate();
  }

  configured = false;
}

bool Context::dispatch_event( string task, string event_type, bool reverse_order )
{
  TaskPhase task_phase( task );
  if (task_phases.find(task_phase.task) == task_phases.end()) return true;

  vector<string>& phases = task_phases[task_phase.task];
  if (task_phase.phase == "*")
  {
    if (reverse_order)
    {
      for (int i=(int)phases.size(); --i>=0; )
      {
        Operation* operation = operations[phases[i]];
        if (operation)
        {
          if ( !operation->handle_event(event_type,reverse_order) ) return false;
        }
      }
      return true;
    }
    else
    {
      for (auto phase : phases)
      {
        Operation* operation = operations[phase];
        if (operation)
        {
          if ( !operation->handle_event(event_type) ) return false;
        }
      }
      return true;
    }
  }
  else
  {
    Operation* operation = operations[ task ];
    if (operation) return operation->handle_event( event_type, reverse_order );
    else           return true;
  }


}

bool Context::execute( string task )
{
  TaskPhase task_phase( task );
  if (task_phases.find(task_phase.task) == task_phases.end()) return true;

  vector<string>& phases = task_phases[task_phase.task];
  for (auto phase : phases)
  {
    Operation* operation = operations[phase];
    if (operation)
    {
      if ( !operation->execute() ) return false;
    }
  }
  return true;
}

void Context::recreate_swapchain()
{
  dispatch_event( "configure", "surface_lost", true );
  configure();
}

void Context::set_operation( string task, Operation* operation )
{
  Operation* existing = operations[task];
  if (existing)
  {
    delete existing;
  }
  else
  {
    // This task.phase does not yet exist in task_phases.
    TaskPhase task_phase( task );
    task_phases[ task_phase.task ].push_back( task );
  }
  operations[task] = operation;
}
