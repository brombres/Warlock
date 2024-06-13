#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct DataReader
  {
    const unsigned char* data;
    int                  count;
    int                  position;

    DataReader( const char* data, int count ) : data((const unsigned char*)data), count(count), position(0) {}

    int   read_byte();
    int   read_int32();
    int   read_int32x();
    float read_real32();
    void  skip( int n );
  };
};

