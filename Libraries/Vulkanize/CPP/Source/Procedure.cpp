#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

Procedure::~Procedure()
{
  if (next_sibling) delete next_sibling;
  if (first_child)  delete first_child;
}

void Procedure::add_child( Procedure* child )
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

void Procedure::add_sibling( Procedure* sibling )
{
  if (parent)
  {
    parent->add_child( sibling );
  }
  else
  {
    sibling->detach();
    Procedure* cur = this;
    while (cur->next_sibling) cur = cur->next_sibling;
    cur->next_sibling = sibling;
    sibling->previous_sibling = this;
  }
}

bool Procedure::configure()
{
  on_configure();
  if (not configured) return false;

  if (first_child && !first_child->configure()) return false;
  if (next_sibling && !next_sibling->configure()) return false;

  return true;
}

void Procedure::detach()
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

bool Procedure::destroy()
{
  if (next_sibling) next_sibling->destroy();
  if (first_child)  first_child->destroy();

  if (configured)
  {
    configured = false;
    on_destroy();
  }

  return false;  // always returns false
}

bool Procedure::render()
{
  return true;
}

void Procedure::remove_child( Procedure* child )
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
    Procedure* cur = child->first_child;
    while (cur->next_sibling != child)
    {
      cur = cur->next_sibling;
    }
    cur->next_sibling = cur->next_sibling->next_sibling;
    cur->next_sibling->previous_sibling = cur;
    child->next_sibling = child->previous_sibling = nullptr;
  }
}
