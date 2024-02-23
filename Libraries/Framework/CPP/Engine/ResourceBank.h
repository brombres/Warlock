#ifndef WARLOCK_RESOURCE_BANK_H
#define WARLOCK_RESOURCE_BANK_H

#pragma once

template <typename ResourceType>
struct ResourceBank
{
  ArrayList<ResourceType> resources;
  ArrayList<int>          ids;
  ArrayList<int>          free_ids;
  int                     count = 0;

  ResourceBank()
  {
    resources.add( ResourceType() ); // prevent 0 from being an ID
  }

  int add( ResourceType resource )
  {
    ++count;
    if (free_ids.count)
    {
      int id = free_ids.remove_last();
      ids.add( id );
      resources[id] = resource;
      return id;
    }
    else
    {
      int id = resources.count;
      ids.add( id );
      resources.add( resource );
      return id;
    }
  }

  ResourceBank& clear()
  {
    resources.clear();
    resources.add( ResourceType() ); // prevent 0 from being an ID
    ids.clear();
    free_ids.clear();
    count = 0;
    return *this;
  }

  ResourceType& operator[]( int id )
  {
    return resources[id];
  }

  ResourceType remove( int id )
  {
    --count;
    ResourceType result = resources[id];
    resources[id] = ResourceType();
    ids.remove( id );
    free_ids.add( id );
    return result;
  }
};

#endif // WARLOCK_RESOURCE_BANK_H
