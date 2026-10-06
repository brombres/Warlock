$input v_color0, v_texcoord0, v_texcoord1

// frame_progress.x: 0.0 = current frame (texture 0), 1.0 = next frame (texture 1)
uniform vec4 frame_progress;

#include <bgfx_shader.sh>
#include "defs.sh"

SAMPLER2D( s_texture_0, 0 );
SAMPLER2D( s_texture_1, 1 );

void main()
{
  vec4 cur_color  = texture2D( s_texture_0, v_texcoord0 );
  vec4 next_color = texture2D( s_texture_1, v_texcoord1 );
  gl_FragColor = mix( cur_color, next_color, frame_progress.x ) * v_color0;
}
