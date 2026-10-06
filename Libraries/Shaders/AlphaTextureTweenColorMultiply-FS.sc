$input v_color0, v_texcoord0

uniform vec4 frame_progress;

#include <bgfx_shader.sh>
#include "defs.sh"

SAMPLER2D( s_texture_0, 0 );
SAMPLER2D( s_texture_1, 1 );

void main()
{
  vec4 cur_color  = texture2D( s_texture_0, v_texcoord0 );
  vec4 next_color = texture2D( s_texture_1, v_texcoord0 );

  //gl_FragColor = mix( cur_color, next_color, frame_progress.x ) * v_color0;
  float v = (next_color.r - cur_color.r) * 32;
  gl_FragColor = vec4( v, v, v, 1 );
}
