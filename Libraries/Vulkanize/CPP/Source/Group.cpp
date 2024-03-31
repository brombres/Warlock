#include "Vulkanize/Vulkanize.h"
using namespace VKZ;
using namespace std;

// Destructor
Group::~Group()
{
  if (operations)
  {
    delete operations;
    operations = nullptr;
  }
}

//----- Event Handling -----------------------------------------------------
bool Group::handle_event( string event_type, bool reverse_order, bool include_siblings )
{
  if (reverse_order)
  {
    if (include_siblings && next_sibling && !next_sibling->handle_event(event_type,true,true))
    {
      return false;
    }
    if (first_child && !first_child->handle_event(event_type,true,true)) return false;
  }

  if (operations && !operations->handle_event(event_type,reverse_order,true)) return false;

  if ( !reverse_order )
  {
    if (first_child && !first_child->handle_event(event_type,false,true)) return false;
    if (include_siblings && next_sibling && !next_sibling->handle_event(event_type,false,true))
    {
      return false;
    }
  }

  return true;
}

bool Group::configure( bool include_siblings )
{
  if (operations && !operations->configure(true)) return false;
  if (first_child && !first_child->configure(true)) return false;
  if (include_siblings && next_sibling && !next_sibling->configure(true)) return false;
  return true;
}

void Group::deactivate( bool include_siblings )
{
  if (include_siblings && next_sibling) next_sibling->deactivate(true);
  if (first_child)  first_child->deactivate(true);
  if (operations) operations->deactivate(true);
}

bool Group::execute( bool include_siblings )
{
  if (operations && !operations->execute(true)) return false;
  if (first_child && !first_child->execute(true)) return false;
  if (include_siblings && next_sibling && !next_sibling->execute(true)) return false;
  return true;
}

//----- Path Operations ----------------------------------------------------
void Group::add_operation( std::string& path, Operation* operation )
{
}

Group* Group::find_group( std::string& path, bool create_missing=false )
{
  string next_segment, remaining_path;
  if (split_first_path_segment(path, next_segment, remaining_path))
  {
    Group* cur = first_child;
    while (cur)
    {
      if (cur->segment == next_segment)
      {
        return cur->find_group( remaining_path, create_missing );
      }
      cur = cur->next_sibling;
    }

    if (create_missing)
    {
      Group* new_group = new Group( path );
      add_child( new_group );
      return new_group->find_group( remaining_path, create_missing );
    }

    return nullptr;
  }
  else
  {
    // 'path' is a single segment; look for a child group with the name.
    Group* cur = first_child;
    while (cur)
    {
      if (cur->segment == path) return cur;
      cur = cur->next_sibling;
    }

    if (create_missing)
    {
      Group* new_group = new Group( path );
      add_child( new_group );
      return new_group;
    }

    return nullptr;
  }
}

void Group::set_operation( std::string& path, Operation* operation )
{
}


bool Group::split_first_path_segment( std::string& path, std::string& first, std::string& remainder )
{
  auto i = path.find( '.' );
  if (i == string::npos) return false;

  first = path.substr( 0, i );
  remainder = path.substr( i+1 );

  return true;
}

bool Group::split_last_path_segment( std::string& path, std::string& preceding, std::string& last )
{
  auto i = path.rfind( '.' );
  if (i == string::npos) return false;

  preceding = path.substr( 0, i );
  last = path.substr( i+1 );

  return true;
}

