#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  enum RenderCmd
  {
    // Each RenderCmd is preceded by skip_count:IntX
    END_DRAWING,
    DRAW_LINES,          // line_count:IntX, line_count * 2 * [x,y,z,w:Real32, argb:Int32]
    DRAW_TRIANGLES,      // triangle_count:IntX, triangle_count * 3 * [x,y,z,w:Real32, argb:Int32]
    DRAW_TEXTURED_TRIANGLES, // texture_id:IntX, triangle_count:IntX,
                             // triangle_count * 3 * [x,y,z,w:Real32, argb:Int32, u,v:Real32]
    DEFINE_TEXTURE,      // [id, width, height:IntX], argb:Int32s
    FREE_TEXTURE,        // id:IntX
    DEFINE_SHADER_STAGE, // skip_count:IntX, id:IntX, stage:IntX, filename:String, main_fn_name:String,
                         // is_string:Logical, [source:String | spirv:Byte[]]
                         //
                         // stage: VERTEX = 1
                         //        TESSELLATION_CONTROL = 2
                         //        TESSELLATION_EVALUATION = 4
                         //        GEOMETRY = 8
                         //        FRAGMENT = 16
    FREE_SHADER_STAGE,   // id:IntX
    DEFINE_SHADER,       // id:IntX, stage_count:IntX, stage_id:IntX[stage_count]
    FREE_SHADER,         // id:IntX
    DEFINE_MATERIAL,     // id:IntX, topology:IntX, primitive_restart:Logical, shader_id:IntX
                         // - Other settings TODO.
                         // - 'topology' uses Vulkan VkPrimitiveTopology values.
    FREE_MATERIAL        // id:IntX
  };
};
