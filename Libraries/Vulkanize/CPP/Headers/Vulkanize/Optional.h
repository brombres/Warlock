#pragma once

namespace VKZ
{
  template<typename DataType>
  struct Optional
  {
    DataType value;
    bool     exists;

    Optional() : value(DataType()), exists(false) {}
    Optional( DataType value ) : value(value), exists(true) {}
    Optional( Optional &existing ) : value(existing.value), exists(existing.exists) {}

    Optional& operator=( Optional& other )
    {
      value = other.value;
      exists = other.exists;
    }
  };
};
