#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  enum class RenderCmdType
  {
    DRAW_LINES       // line count
  };

  struct RenderCmd
  {
    RenderCmdType type;
    int           vertex_count;

    RenderCmd( RenderCmdType type, int vertex_count=0 ) : type(type), vertex_count(vertex_count) {}
  };
};
