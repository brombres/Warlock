#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct Color
  {
    UInt32 argb;

    Color( UInt32 argb ) : argb(argb) {}

    Color( int r, int g, int b, int a=255 ) : argb( (a<<24) | (r<<16) | (g<<8) | b ) {}

    UInt32 abgr()
    {
      return (argb & 0xFF00FF00) | ((argb<<16) & 0x00FF0000) | ((argb>>16) & 0x000000FF);
    }
  };
};
