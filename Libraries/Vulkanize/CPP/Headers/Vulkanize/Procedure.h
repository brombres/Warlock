#pragma once

namespace VKZ
{
  struct Procedure
  {
    Procedure* parent           = nullptr;
    Procedure* first_child      = nullptr;
    Procedure* last_child       = nullptr;
    Procedure* next_sibling     = nullptr;
    Procedure* previous_sibling = nullptr;
    bool       configured       = false;

    Procedure() {}
    virtual ~Procedure();

    virtual bool on_configure() { return false; }
    // Called from configure(), which is called at the appropriate phase in the Context
    // configuration configuration_phases. Set 'configured' to true to indicate that the procedure
    // has been successfully configured or at least that there is no fatal error.
    // Leave 'configured' as false to indicate a fatal error.

    virtual void on_destroy() {}
    // Called from destroy() if on_configure() set 'configured' to true.

    virtual bool on_render() { return true; }

    virtual void add_child( Procedure* child );
    virtual void add_sibling( Procedure* sibling );
    virtual bool configure();
    virtual void detach();  // detach from parent and siblings; preserves children
    virtual bool destroy(); // always returns false, allowing on_configure() to easily destroy() and return false.
    virtual bool render();
    virtual void remove_child( Procedure* child );
  };
};
