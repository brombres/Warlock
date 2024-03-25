#pragma once

namespace VKZ
{
  struct Component
  {
    Component* parent           = nullptr;
    Component* first_child      = nullptr;
    Component* last_child       = nullptr;
    Component* next_sibling     = nullptr;
    Component* previous_sibling = nullptr;
    bool       configured       = false;

    Component() {}
    virtual ~Component();

    virtual void on_configure() { configured = true; }
    // Called from configure(), which is called at the appropriate phase in the Context
    // configuration phases. Set 'configured' to true to indicate that the component
    // has been successfully configured or at least that there is no fatal error.
    // Leave 'configured' as false to indicate a fatal error.

    virtual void on_destroy() { configured = false; }
    // Called from destroy() if 'configured' has been set to true.

    virtual void add_child( Component* child );
    virtual void add_sibling( Component* sibling );
    virtual bool configure();
    virtual void detach();  // detach from parent and siblings; preserves children
    virtual bool destroy(); // always returns false, allowing on_configure() to easily destroy() and return false.
    virtual void remove_child( Component* child );
  };
};
