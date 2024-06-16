#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  enum RenderCmd
  {
    END_DRAWING,
    DRAW_LINES,      // line_count:IntX, line_count * 2 * [x,y,z,w:Real32, argb:Int32]
    DRAW_TRIANGLES,  // triangle_count:IntX, triangle_count * 3 * [x,y,z,w:Real32, argb:Int32]
    DRAW_TEXTURED_TRIANGLES, // texture_id:IntX, triangle_count:IntX,
                             // triangle_count * 3 * [x,y,z,w:Real32, argb:Int32, u,v:Real32]
    DEFINE_TEXTURE,  // [id, width, height:IntX], argb:Int32s
    FREE_TEXTURE     // id:IntX
  };
};
