#ifndef WARLOCK_RESOURCE_BANK_H
#define WARLOCK_RESOURCE_BANK_H

#pragma once

#include "ArrayList.h"

template <typename IDType, typename ResourceType>
struct ResourceBank
{
  ArrayList<ResourceType> resources;
  ArrayList<IDType>       ids;
  ArrayList<IDType>       free_ids;
  int                     count = 0;

  ResourceBank()
  {
    resources.add( ResourceType() ); // prevent 0 from being an ID
  }

  IDType add( ResourceType resource )
  {
    ++count;
    if (free_ids.count)
    {
      IDType id = free_ids.remove_last();
      ids.add( id );
      resources[id] = resource;
      return id;
    }
    else
    {
      IDType id = resources.count;
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

  ResourceType& operator[]( IDType id )
  {
    return resources[id];
  }

  ResourceType remove( IDType id )
  {
    --count;
    ResourceType result = resources[id];
    resources[id] = ResourceType();
    ids.remove( id );
    free_ids.add( id );
    return result;
  }

  ResourceType remove_last( IDType id )
  {
    return remove( ids.last() );
  }
};

#endif // WARLOCK_RESOURCE_BANK_H
