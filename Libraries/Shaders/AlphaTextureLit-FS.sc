$input v_color0, v_texcoord0, v_normal

#include <bgfx_shader.sh>

uniform vec4 u_mipmap_level;

SAMPLER2D(s_texColor,0);

void main()
{
  vec3 lighting = vec3( 1, 1, 1 );
  if (u_mipmap_level.x == -1)
  {
    vec4 texColor = texture2D( s_texColor, v_texcoord0 ); // Sample the texture w/auto-mipmap LOD
    texColor *= v_color0;
    gl_FragColor = vec4(texColor.rgb * lighting, texColor.a);
  }
  else
  {
    vec4 texColor = texture2DLod( s_texColor, v_texcoord0, u_mipmap_level.x ); // Sample the texture @specified LOD
    texColor *= v_color0;
    gl_FragColor = vec4(texColor.rgb * lighting, texColor.a);
  }
}
