#ifndef BALEFIRE_RESOURCE_BANK_H
#define BALEFIRE_RESOURCE_BANK_H

#pragma once

#include <vector>
#include <unordered_map>

namespace BALEFIRE
{

  template <typename IDType, typename ResourceType>
  struct ResourceBank
  {
    std::vector<ResourceType>         resources;
    std::vector<IDType>               ids;
    std::vector<IDType>               free_ids;
    std::unordered_map<IDType,size_t> id_index_lookup;
    int                               count = 0;

    ResourceBank()
    {
      resources.push_back( ResourceType() ); // prevent 0 from being an ID
    }

    IDType add( ResourceType resource )
    {
      ++count;
      if (free_ids.size())
      {
        IDType id = free_ids.back();
        free_ids.pop_back();
        id_index_lookup[id] = ids.size();
        ids.push_back( id );
        resources[id] = resource;
        return id;
      }
      else
      {
        IDType id = (IDType) resources.size();
        id_index_lookup[(IDType)id] = ids.size();
        ids.push_back( id );
        resources.push_back( resource );
        return id;
      }
    }

    ResourceBank& clear()
    {
      resources.clear();
      resources.push_back( ResourceType() ); // prevent 0 from being an ID
      ids.clear();
      free_ids.clear();
      id_index_lookup.clear();
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
      size_t i1 = id_index_lookup[id];
      size_t i2 = ids.size() - 1;
      ids[i1] = ids[i2];
      id_index_lookup[(IDType)i2] = i1;
      ids.pop_back();
      free_ids.push_back( id );
      return result;
    }

    ResourceType remove_last()
    {
      return remove( ids.back() );
    }
  };

};

#endif // BALEFIRE_RESOURCE_BANK_H
