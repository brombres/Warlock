#pragma once

#include "Balefire/Vulkan/RendererVulkan.h"

namespace BALEFIRE
{
  struct Vertex
  {
    struct { float x, y, z; } position;
    uint32_t color;
    uint32_t data;
    struct { float u, v; }    uv;

    Vertex( float x, float y, float z, uint32_t color ) : color(color)
    {
      position = { x, y, z };
    }
  };
};

