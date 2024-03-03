#ifndef BALEFIRE_REF_H
#define BALEFIRE_REF_H

#pragma once

#include <cstdio>

namespace BALEFIRE
{

template <typename DataType>
struct Ref
{
  DataType* data = nullptr;

  Ref<DataType>()
  {
  }

  Ref<DataType>( DataType* data )
  {
    this->data = data;
    if (data) data->retain();
  }

  Ref<DataType>( Ref<DataType> const &existing )
  {
    if ((data=existing.data)) data->retain();
  }

  ~Ref<DataType>()
  {
    if (data)
    {
      data->release();
      data = nullptr;
    }
  }

  Ref<DataType>& operator=( DataType* new_data )
  {
    if (new_data) new_data->retain();
    if (data) data->release();
    data = new_data;
    return *this;
  }

  Ref<DataType>& operator=( Ref<DataType> &other )
  {
    if (other.data) other.data->retain();
    if (data) data->release();
    data = other.data;
    return *this;
  }

  operator bool()
  {
    return !!data;
  }

  operator DataType*()
  {
    return data;
  }

  DataType* operator->()
  {
    return data;
  }
};

}; // namespace BALEFIRE

#endif // BALEFIRE_REF_H
