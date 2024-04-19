#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct StandardVertex
  {
    struct { float x, y, z; } position;
    struct { float x, y, z; } normal;
    struct { float u, v; }    uv;
    struct { float u, v; }    uv2;
    float    data;
    uint32_t color;
  };
};

