#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

Operation::~Operation()
{
  if (next_sibling) delete next_sibling;
  if (first_child)  delete first_child;
}

bool Operation::handle_event( int event_type )
{
  switch (event_type)
  {
    case VKZ_EVENT_CONFIGURE:
      if (configured) return true;

      if ( !on_configure() ) return false;
      configured = true;
      break;

    case VKZ_EVENT_EXECUTE:
      if ( !configured )
      {
        if ( !on_configure() ) return false;
        configured = true;
      }

      if ( !on_execute() ) return false;
      break;

    case VKZ_EVENT_DEACTIVATE:
      if (configured)
      {
        configured = false;
        on_deactivate();
      }
      break;

    case VKZ_EVENT_SURFACE_LOST:
      on_surface_lost();
      break;

    default:
      if ( !on(event_type) ) return false;
  }

  if (first_child && !first_child->handle_event(event_type)) return false;
  if (next_sibling && !next_sibling->handle_event(event_type)) return false;

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

void Operation::add_child( Operation* child )
{
  child->parent = this;

  if (first_child)
  {
    last_child->next_sibling = child;
    child->previous_sibling = last_child;
    last_child = child;
  }
  else
  {
    first_child = last_child = child;
  }
}

void Operation::add_sibling( Operation* sibling )
{
  if (parent)
  {
    parent->add_child( sibling );
  }
  else
  {
    sibling->detach();
    Operation* cur = this;
    while (cur->next_sibling) cur = cur->next_sibling;
    cur->next_sibling = sibling;
    sibling->previous_sibling = this;
  }
}

void Operation::detach()
{
  if (parent)
  {
    parent->remove_child( this );
    parent = nullptr;
  }
  else
  {
    if (previous_sibling)
    {
      previous_sibling->next_sibling = next_sibling;
      previous_sibling = nullptr;
    }
    if (next_sibling)
    {
      next_sibling->previous_sibling = next_sibling;
      next_sibling = nullptr;
    }
  }
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

void Operation::reconfigure()
{
}

void Operation::remove_child( Operation* child )
{
  if (child->parent != this) return;
  child->parent = nullptr;

  if (child == first_child)
  {
    if (child == last_child)
    {
      first_child = last_child = nullptr;
    }
    else
    {
      first_child = child->next_sibling;
      child->next_sibling = nullptr;
    }
  }
  else if (child == last_child)
  {
    last_child = child->previous_sibling;
    child->previous_sibling = nullptr;
  }
  else
  {
    Operation* cur = child->first_child;
    while (cur->next_sibling != child)
    {
      cur = cur->next_sibling;
    }
    cur->next_sibling = cur->next_sibling->next_sibling;
    cur->next_sibling->previous_sibling = cur;
    child->next_sibling = child->previous_sibling = nullptr;
  }
}
