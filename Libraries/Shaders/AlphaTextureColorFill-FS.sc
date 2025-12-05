$input v_color0, v_texcoord0

#include <bgfx_shader.sh>
#include "defs.sh"

SAMPLER2D(s_texture,0);

void main()
{
  float a = texture2D( s_texture, v_texcoord0 ).a;
  gl_FragColor = v_color0 * a;
}
