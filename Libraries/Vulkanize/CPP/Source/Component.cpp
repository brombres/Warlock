#include "Vulkanize/Component.h"
#include "Vulkanize/Context.h"
using namespace VULKANIZE;

Component::~Component()
{
  if (next_sibling) delete next_sibling;
  if (first_child)  delete first_child;
}

void Component::add_child( Component* child )
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

void Component::add_sibling( Component* sibling )
{
  if (parent)
  {
    parent->add_child( sibling );
  }
  else
  {
    sibling->detach();
    Component* cur = this;
    while (cur->next_sibling) cur = cur->next_sibling;
    cur->next_sibling = sibling;
    sibling->previous_sibling = this;
  }
}

bool Component::configure()
{
  on_configure();
  if (not configured) return false;

  if (first_child && !first_child->configure()) return false;
  if (next_sibling && !next_sibling->configure()) return false;

  return true;
}

void Component::detach()
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

bool Component::destroy()
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

void Component::remove_child( Component* child )
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
    Component* cur = child->first_child;
    while (cur->next_sibling != child)
    {
      cur = cur->next_sibling;
    }
    cur->next_sibling = cur->next_sibling->next_sibling;
    cur->next_sibling->previous_sibling = cur;
    child->next_sibling = child->previous_sibling = nullptr;
  }
}
