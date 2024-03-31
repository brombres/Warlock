#include "Vulkanize/Vulkanize.h"
using namespace VKZ;
using namespace std;

Operation::~Operation()
{
  if (next_sibling) delete next_sibling;
  if (first_child)  delete first_child;

  if (parent)
  {
    parent->remove_child( this );
  }
}

bool Operation::handle_event( string event_type, bool reverse_order )
{
  if (reverse_order)
  {
    if (next_sibling && !next_sibling->handle_event(event_type)) return false;
    if (first_child && !first_child->handle_event(event_type)) return false;
  }

  if ( !configured )
  {
    if ( !on_configure() ) return false;
    configured = true;
  }

  if ( !on(event_type) ) return false;

  if ( !reverse_order )
  {
    if (first_child && !first_child->handle_event(event_type)) return false;
    if (next_sibling && !next_sibling->handle_event(event_type)) return false;
  }

  return true;

}

bool Operation::configure()
{
  if (configured) return true;

  if (not on_configure()) return false;
  configured = true;

  if (first_child && !first_child->configure()) return false;
  if (next_sibling && !next_sibling->configure()) return false;

  return true;
}

void Operation::deactivate()
{
  if (next_sibling) next_sibling->deactivate();
  if (first_child)  first_child->deactivate();

  if (configured)
  {
    configured = false;
    on_deactivate();
  }
}

bool Operation::execute()
{
  configure();
  if ( !on_execute() ) return false;

  if (first_child && !first_child->execute()) return false;
  if (next_sibling && !next_sibling->execute()) return false;
  return true;
}

