#pragma once

namespace VKZ
{
  struct Action
  {
    Action* parent           = nullptr;
    Action* first_child      = nullptr;
    Action* last_child       = nullptr;
    Action* next_sibling     = nullptr;
    Action* previous_sibling = nullptr;
    bool    is_active        = false;

    //----- Constructor/Destructor ---------------------------------------------
    Action() {}
    virtual ~Action();

    //----- Event Callbacks ----------------------------------------------------
    virtual bool on_activate() { return true; }
    // Return true on success, false on failure.

    virtual void on_deactivate() {}
    // Called from deactivate() if on_activate() returned true.

    virtual bool on_execute() { return true; }
    // Return true on success, false on failure.

    //----- Event Handling Framework -------------------------------------------
    virtual bool activate();
    virtual void deactivate();
    virtual bool execute();

    //----- Tree Operations ----------------------------------------------------
    virtual void add_child( Action* child );
    virtual void add_sibling( Action* sibling );
    virtual void detach();  // detach from parent and siblings; preserves children
    virtual void remove_child( Action* child );
  };
};
