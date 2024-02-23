#ifndef WARLOCK_ARRAYLIST_H
#define WARLOCK_ARRAYLIST_H

#pragma once

template <typename DataType>
struct ArrayList
{
  int count      = 0;
  int capacity   = 0;
  DataType* data = nullptr;

  ArrayList() {}

  ArrayList( int initial_capacity )
  {
    reserve( initial_capacity );
  }

  ~ArrayList()
  {
    if (data)
    {
      delete [] data;
      data = nullptr;
    }
  }

  ArrayList& add( DataType value )
  {
    reserve( 1 )[ count++ ] = value;
    return *this;
  }

  ArrayList& clear()
  {
    int n = count;
    DataType* data = this->data;
    while (--n >= 0) data[n] = DataType();
    count = 0;
    return *this;
  }

  int locate( DataType value )
  {
    for (int i=0, n=count; --n>=0; ++i)
    {
      if (data[i] == value) return i;
    }
    return -1;
  }

  DataType& operator[]( int index )
  {
    return data[index];
  }

  bool remove( DataType value )
  {
    int index = locate( value );
    if (index == -1) return false;
    remove_at( index );
    return true;
  }

  DataType remove_at( int index )
  {
    DataType result = data[index];
    for (int i=index, n=(--count-index); --n>=0; ++i)
    {
      data[i] = data[i+1];
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

  ArrayList& reserve( int additional_elements )
  {
    int required_capacity = count + additional_elements;
    if (required_capacity <= capacity) return *this;

    if (data)
    {
      int min_expansion = capacity * 2;
      if (min_expansion > required_capacity) required_capacity = min_expansion;
      DataType* new_data = new DataType[ required_capacity ];
      for (int i=0, n=count; --n>=0; ++i) new_data[i] = data[i];
      delete [] data;
      data = new_data;
    }
    else
    {
      if (required_capacity < 10) required_capacity = 10;
      data = new DataType[ required_capacity ];
    }
    capacity = required_capacity;
    return *this;
  }
};
#endif // WARLOCK_ARRAYLIST_H
