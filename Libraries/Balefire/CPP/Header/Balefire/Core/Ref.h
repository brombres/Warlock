#ifndef BALEFIRE_REF_H
#define BALEFIRE_REF_H

#pragma once

#include <cstdio>

namespace Balefire
{

template <typename DataType>
struct Ref
{
  DataType* data = nullptr;

  Ref<DataType>() {}

  Ref<DataType>( DataType* data )
  {
    this->data = data;
    if (data) data->retain();
  }

  Ref<DataType>( Ref<DataType> const &existing )
  {
    if ((data=existing.data)) data->retain();
  }

  ~Ref()
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

  DataType* operator->()
  {
    return data;
  }
};

}; // namespace Balefire

#endif // BALEFIRE_REF_H
