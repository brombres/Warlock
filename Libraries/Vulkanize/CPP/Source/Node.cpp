#include "Vulkanize/Node.h"
using namespace VULKANIZE;

Node::~Node()
{
  destroy();
}

void Node::add( Node* child )
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

void Node::destroy()
{
  if (parent) parent->remove_child( this );

  while (last_child) delete last_child;
  on_destroy();
}

void Node::remove_child( Node* child )
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
    Node* cur = child->first_child;
    while (cur->next_sibling != child)
    {
      cur = cur->next_sibling;
    }
    cur->next_sibling = cur->next_sibling->next_sibling;
    cur->next_sibling->previous_sibling = cur;
    child->next_sibling = child->previous_sibling = nullptr;
  }
}

