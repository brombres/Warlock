$input v_color0, v_texcoord0

#include <bgfx_shader.sh>
#include "defs.sh"

SAMPLER2D(s_texture_0,0);

void main()
{
  vec4 texColor = texture2D( s_texture_0, v_texcoord0 );
  gl_FragColor = texColor * v_color0;
}
