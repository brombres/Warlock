#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

Action::~Action()
{
  if (next_sibling) delete next_sibling;
  if (first_child)  delete first_child;
}

bool Action::activate()
{
  if (is_active) return true;

  if (not on_activate()) return false;
  is_active = true;

  if (first_child && !first_child->activate()) return false;
  if (next_sibling && !next_sibling->activate()) return false;

  return true;
}

void Action::add_child( Action* child )
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

void Action::add_sibling( Action* sibling )
{
  if (parent)
  {
    parent->add_child( sibling );
  }
  else
  {
    sibling->detach();
    Action* cur = this;
    while (cur->next_sibling) cur = cur->next_sibling;
    cur->next_sibling = sibling;
    sibling->previous_sibling = this;
  }
}

void Action::detach()
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

void Action::deactivate()
{
  if (next_sibling) next_sibling->deactivate();
  if (first_child)  first_child->deactivate();

  if (is_active)
  {
    is_active = false;
    on_deactivate();
  }
}

bool Action::execute()
{
  activate();
  if ( !on_execute() ) return false;

  if (first_child && !first_child->execute()) return false;
  if (next_sibling && !next_sibling->execute()) return false;
  return true;
}

void Action::remove_child( Action* child )
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
    Action* cur = child->first_child;
    while (cur->next_sibling != child)
    {
      cur = cur->next_sibling;
    }
    cur->next_sibling = cur->next_sibling->next_sibling;
    cur->next_sibling->previous_sibling = cur;
    child->next_sibling = child->previous_sibling = nullptr;
  }
}
