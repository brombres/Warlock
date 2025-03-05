$input v_color0, v_texcoord0

#include <bgfx_shader.sh>

uniform vec4 u_mipmaps;

SAMPLER2D(s_texColor,0);

void main()
{
  if (u_mipmaps.x)
  {
    vec4 texColor = texture2D( s_texColor, v_texcoord0 ); // Sample the texture w/auto-mipmap LOD
    gl_FragColor = texColor * v_color0; // Output the texture color
  }
  else
  {
    vec4 texColor = texture2DLod( s_texColor, v_texcoord0, 0.0 ); // Sample the texture, no mimaps (LOD 0).
    gl_FragColor = texColor * v_color0; // Output the texture color
  }
}
