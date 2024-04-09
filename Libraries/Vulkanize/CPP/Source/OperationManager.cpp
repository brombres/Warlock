#include <cstdio>

#include "Vulkanize/Vulkanize.h"
using namespace VKZ;
using namespace std;

OperationManager::~OperationManager()
{
  destroy();

  for (auto phase : phases)
  {
    Operation* operation = operations[phase];
    if (operation) delete operation;
  }
  phases.clear();
  operations.clear();
}

void OperationManager::add_operation( string phase, Operation* operation )
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

bool OperationManager::activate( string phase )
{
  if ( !dispatch_event(phase, "activate") ) return false;
  return true;
}

bool OperationManager::configure()
{
  if (configured) return true;
  if ( !operations.size() ) configure_operations();
  if ( !activate("configure") ) return false;
  configured = true;
  return true;
}

void OperationManager::configure_operations()
{
}

void OperationManager::deactivate( string phase )
{
  dispatch_event( phase, "deactivate", true );
}

void OperationManager::destroy()
{
  deactivate( "configure" );
  configured = false;
}

bool OperationManager::dispatch_event( string phase, string event, bool reverse_order )
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

bool OperationManager::execute( string phase )
{
  return dispatch_event( phase, "execute" );
}

void OperationManager::set_operation( string phase, Operation* operation )
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

bool OperationManager::_phase_begins_with( const string& phase, const string& other )
{
  auto value_n = phase.size();
  auto n = other.size();
  if (value_n < n) return false;

  if (0 != phase.compare(0,n,other)) return false;
  if (value_n == n) return true;
  return (phase[n] == '.');
}
