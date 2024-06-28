#pragma once

#include <string>
#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct DataReader
  {
    unsigned char* data;
    int            count;
    int            position;

    DataReader( unsigned char* data, int count ) : data((unsigned char*)data), count(count), position(0) {}

    int            read_byte();
    int            read_bytes( unsigned char** data_pointer );
    int            read_int32s( int** data_pointer );
    int            read_int32();
    int            read_int32x();
    bool           read_logical();
    float          read_real32();
    std::string    read_string();
    void           seek( int pos );
    void           skip( int n );
  };
};

