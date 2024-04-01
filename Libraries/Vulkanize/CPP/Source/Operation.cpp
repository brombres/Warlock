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

bool Operation::handle_event( string event, bool reverse_order )
{
  if (reverse_order)
  {
    if (next_sibling && !next_sibling->handle_event(event)) return false;
    if (first_child && !first_child->handle_event(event)) return false;
  }

  if (event == "deactivate")
  {
    if (configured)
    {
      deactivate();
      configured = false;
    }
  }
  else
  {
    bool is_configure = (event == "configure");
    if (is_configure || event == "execute")
    {
      if ( !configured )
      {
        if ( !configure() ) return false;
        configured = true;
      }

      if ( !is_configure && !execute() ) return false;
    }
    else
    {
      if ( !on_event(event) ) return false;
    }
  }

  if ( !reverse_order )
  {
    if (first_child && !first_child->handle_event(event)) return false;
    if (next_sibling && !next_sibling->handle_event(event)) return false;
  }

  return true;

}

