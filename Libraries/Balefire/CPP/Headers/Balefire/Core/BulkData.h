#ifndef BALEFIRE_BULK_DATA_H
#define BALEFIRE_BULK_DATA_H

#pragma once

#include <cstring>
#include "Balefire/Core/Types.h"

namespace BALEFIRE
{

template <typename DataType>
struct BulkData
{
  Int64 count    = 0;
  Int64 capacity = 0;
  DataType* data = nullptr;
  Byte internal_data[176];

  BulkData()
  {
    data = (DataType*)internal_data;
    capacity = (Int64)(sizeof(internal_data) / sizeof(DataType));
  }

  BulkData( Int64 initial_capacity ) : BulkData()
  {
    reserve( initial_capacity );
  }

  ~BulkData()
  {
    if ((void*)data != (void*)internal_data)
    {
      delete [] data;
    }
    data = nullptr;
  }

  BulkData& add( DataType value )
  {
    reserve( 1 )[ count++ ] = value;
    return *this;
  }

  BulkData& clear()
  {
    if (count)
    {
      memset( data, 0, count*sizeof(DataType) );
      count = 0;
    }
    return *this;
  }

  BulkData& discard_from( Int64 index )
  {
    Int64 n = count - index;
    if (n > 0)
    {
      memset( data+index, 0, n*sizeof(DataType) );
      count = index;
    }
    return *this;
  }

  DataType& last()
  {
    return data[count-1];
  }

  Int64 locate( DataType value )
  {
    for (Int64 i=0, n=count; --n>=0; ++i)
    {
      if (data[i] == value) return i;
    }
    return -1;
  }

  DataType& operator[]( Int64 index )
  {
    return data[index];
  }

  bool remove( DataType value )
  {
    Int64 index = locate( value );
    if (index == -1) return false;
    remove_at( index );
    return true;
  }

  DataType remove_at( Int64 index )
  {
    DataType result = data[index];

    Int64 shift_count = (--count - index);
    if (shift_count)
    {
      memmove( data+index, data+index+1, shift_count*sizeof(DataType) );
    }
    data[count] = DataType();

    return result;
  }

  DataType remove_last()
  {
    DataType result = data[--count];
    data[count] = DataType();
    return result;
  }

  BulkData& reserve( Int64 additional_elements )
  {
    Int64 required_capacity = count + additional_elements;
    if (required_capacity <= capacity) return *this;

    Int64 min_expansion = capacity * 2;
    if (min_expansion > required_capacity) required_capacity = min_expansion;
    DataType* new_data = new DataType[ required_capacity ];
    memcpy( new_data, data, count*sizeof(DataType) );
    if ((void*)data != (void*)internal_data) delete [] data;
    data = new_data;

    capacity = required_capacity;
    return *this;
  }
};

};
#endif // BALEFIRE_BULK_DATA_H
