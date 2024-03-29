#pragma once

namespace VKZ
{
  struct Operation
  {
    Operation* parent           = nullptr;
    Operation* first_child      = nullptr;
    Operation* last_child       = nullptr;
    Operation* next_sibling     = nullptr;
    Operation* previous_sibling = nullptr;
    bool    configured       = false;

    //----- Constructor/Destructor ---------------------------------------------
    Operation() {}
    virtual ~Operation();

    //----- Event Callbacks ----------------------------------------------------
    virtual bool on( int event_type ) { return true; }

    virtual bool on_configure() { return true; }
    // Return true on success, false on failure.

    virtual bool on_execute() { return true; }
    // Return true on success, false on failure.

    virtual void on_deactivate() {}
    // Called from deactivate() if on_configure() returned true.

    virtual void on_surface_lost() {}

    //----- Event Handling Framework -------------------------------------------
    virtual bool handle_event( int event_type );
    virtual bool configure();
    virtual bool execute();
    virtual void reconfigure();
    virtual void deactivate();

    //----- Tree Operations ----------------------------------------------------
    virtual void add_child( Operation* child );
    virtual void add_sibling( Operation* sibling );
    virtual void detach();  // detach from parent and siblings; preserves children
    virtual void remove_child( Operation* child );
  };
};
