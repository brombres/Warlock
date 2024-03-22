#pragma once

namespace VULKANIZE
{
  struct Context;

  struct Component
  {
    Context*   context;
    Component* parent           = nullptr;
    Component* first_child      = nullptr;
    Component* last_child       = nullptr;
    Component* next_sibling     = nullptr;
    Component* previous_sibling = nullptr;

    Component( Context* context );
    virtual ~Component();

    virtual void on_destroy() {}

    virtual void add( Component* child );
    virtual void remove_child( Component* child );
  };
};
