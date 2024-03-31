#pragma once

#include <string>

namespace VKZ
{
  template <typename ExtendedType>
  struct Node
  {
    // PROPERTIES
    Node<ExtendedType>* parent           = nullptr;
    Node<ExtendedType>* first_child      = nullptr;
    Node<ExtendedType>* last_child       = nullptr;
    Node<ExtendedType>* next_sibling     = nullptr;
    Node<ExtendedType>* previous_sibling = nullptr;

    // METHODS
    virtual ~Node<ExtendedType>()
    {
      if (next_sibling) delete next_sibling;
      if (first_child)  delete first_child;

      if (parent)
      {
        parent->remove_child( this );
      }
    }

    virtual void add_child( Node<ExtendedType>* child )
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

    virtual void add_sibling( Node<ExtendedType>* sibling )
    {
      if (parent)
      {
        parent->add_child( sibling );
      }
      else
      {
        sibling->detach();
        Node<ExtendedType>* cur = this;
        while (cur->next_sibling) cur = cur->next_sibling;
        cur->next_sibling = sibling;
        sibling->previous_sibling = this;
      }
    }

    virtual void detach()
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

    // Detach from parent and siblings; preserves children
    virtual void remove_child( Node<ExtendedType>* child )
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
        Node<ExtendedType>* cur = child->first_child;
        while (cur->next_sibling != child)
        {
          cur = cur->next_sibling;
        }
        cur->next_sibling = cur->next_sibling->next_sibling;
        cur->next_sibling->previous_sibling = cur;
        child->next_sibling = child->previous_sibling = nullptr;
      }
    }
  };
};
