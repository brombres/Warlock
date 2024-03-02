#ifndef BALEFIRE_REF_COUNTED_H
#define BALEFIRE_REF_COUNTED_H

#pragma once

#include <cstdio>

namespace Balefire
{

struct RefCounted
{
  int refcount = 0;

  ~RefCounted()
  {
    if (refcount)
    {
      fprintf( stderr, "[WARNING] RefCounted object deleted without refcount reaching 0.\n" );
    }
  }
};

template <typename DataType>
struct SmartPointer
{
  DataType* data = nullptr;

  SmartPointer<DataType>() {}

  SmartPointer<DataType>( DataType* data )
  {
    this->data = data;
    if (data) ++data->refcount;
  }

  SmartPointer<DataType>( SmartPointer<DataType> const &existing )
  {
    if ((data=existing.data)) ++data->refcount;
  }

  ~SmartPointer()
  {
    if (data)
    {
      if (!--data->refcount) delete data;
      data = nullptr;
    }
  }

  SmartPointer<DataType>& operator=( DataType* new_data )
  {
    if (new_data) ++new_data->refcount;
    if (data && !--data->refcount) delete data;
    data = new_data;
    return *this;
  }

  SmartPointer<DataType>& operator=( SmartPointer<DataType> &other )
  {
    if (other.data) ++other.data->refcount;
    if (data && !--data->refcount) delete data;
    data = other.data;
    return *this;
  }

  DataType* operator->()
  {
    return data;
  }
};

}; // namespace Balefire

#endif // BALEFIRE_REF_COUNTED_H
