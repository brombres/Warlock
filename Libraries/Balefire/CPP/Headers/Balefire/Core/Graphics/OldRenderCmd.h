#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  enum class OldRenderCmd
  {
    // Each OldRenderCmd is preceded by skip_count:IntX
    END_DRAWING,
    DRAW_LINES,      // material_id:IntX, line_count:IntX, line_count * 2 * [x,y,z,w:Real32, argb:Int32]
    DRAW_TRIANGLES,  // material_id:IntX, triangle_count:IntX,
                     //   triangle_count * 3 * [x,y,z,w:Real32, argb:Int32, u,v:Real32]
    DEFINE_TEXTURE,  // [id, width, height:IntX], argb:Int32s
    FREE_TEXTURE,    // id:IntX
    DEFINE_SHADER,   // id:IntX, stage:IntX, filename:String, main_fn_name:String,
                     //   is_string:Logical, [source:String | spirv:Byte[]]
                     //
                     //   stage: VERTEX = 1
                     //          TESSELLATION_CONTROL = 2
                     //          TESSELLATION_EVALUATION = 4
                     //          GEOMETRY = 8
                     //          FRAGMENT = 16
    FREE_SHADER,     // id:IntX
    DEFINE_MATERIAL, // id:IntX, topology:IntX, primitive_restart:Logical,
                     //   shader_count:IntX, shader_id:IntX[shader_count],
                     //   texture_count:IntX, texture_layer:IntX, texture_id:IntX[texture_count]
                     // - Other settings TODO.
                     // - 'topology' uses Vulkan VkPrimitiveTopology values.
    FREE_MATERIAL    // id:IntX
  };
};
