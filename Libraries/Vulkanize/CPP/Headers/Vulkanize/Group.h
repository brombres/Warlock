#pragma once

#include <string>

namespace VKZ
{
  struct Operation;

  struct Group : Node<Group>
  {
    // PROPERTIES
    std::string segment;
    Operation*  operations = nullptr;

    // METHODS
    // ---- Structors ----------------------------------------------------------
    Group() {}
    Group( std::string& segment ) : segment(segment) {}
    virtual ~Group();

    // ---- Event Handling -----------------------------------------------------
    virtual bool handle_event( std::string event_type, bool reverse_order=false, bool include_siblings=false );
    virtual bool configure( bool include_siblings=false );
    virtual bool execute( bool include_siblings=false );
    virtual void deactivate( bool include_siblings=false );

    // ---- Path Operations ----------------------------------------------------
    virtual void   add_operation( std::string& path, Operation* operation );
    virtual Group* find_group( std::string& path, bool create_missing=false );
    virtual void   set_operation( std::string& path, Operation* operation );

    // GLOBAL METHODS
    static bool split_first_path_segment( std::string& path, std::string& first, std::string& remainder );
    static bool split_last_path_segment( std::string& path, std::string& preceding, std::string& last );
  };
};
