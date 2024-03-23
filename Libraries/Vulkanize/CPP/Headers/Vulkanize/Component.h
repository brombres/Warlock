#pragma once

namespace VULKANIZE
{
  struct Context;

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

    virtual bool configure() { return (configured = true); }
    // Called at the appropriate step in the Context configuration process.

    virtual bool destroy() { return (configured = false); }
    // Only called from destructor if 'configured == true'.
    // Should always return "false" to simply returning "false" from a failed configure().

    virtual void add_child( Component* child );
    virtual void remove_child( Component* child );
  };
};
