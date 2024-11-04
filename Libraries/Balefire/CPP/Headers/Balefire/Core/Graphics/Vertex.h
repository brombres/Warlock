#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct Vertex
  {
    struct { float x, y, z, w; } position;
    UInt32 color;
    struct { float u, v; } uv;
    UInt32 data;

    Vertex( float x, float y, float z, float w, UInt32 color ) : color(color)
    {
      position = { x, y, z, w };
    }

    Vertex( float x, float y, float z, float w, UInt32 color, float u, float v ) : color(color)
    {
      position = { x, y, z, w };
      uv = { u, v };
    }
  };
};

