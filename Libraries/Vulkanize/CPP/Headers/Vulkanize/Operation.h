#pragma once

#include <string>

namespace VKZ
{
  struct Operation : Node<Operation>
  {
    bool        active       = false;

    //----- Constructor/Destructor ---------------------------------------------
    Operation() {}
    virtual ~Operation();

    //----- Event Callbacks ----------------------------------------------------
    virtual bool on_event( std::string event ) { return true; }

    virtual bool activate() { return true; }
    // Return true on success, false on failure.

    virtual bool execute() { return true; }
    // Return true on success, false on failure.

    virtual void deactivate() {}
    // Called from deactivate() if on_configure() returned true.

    //----- Event Handling Framework -------------------------------------------
    virtual bool handle_event( std::string event, bool reverse_order=false );
  };
};
