$input v_color0, v_texcoord0, v_normal

#include <bgfx_shader.sh>

uniform vec4 u_mipmap_level;

SAMPLER2D(s_texColor,0);

void main()
{
  //vec3  light_direction = vec3( 0.5774, 0.5774, -0.5774 );
  vec3  light_direction = vec3( 0, 0, -1 );
  float light_factor = max( dot(v_normal,-light_direction), 0.0 );

  vec3 lighting = vec3( light_factor, light_factor, light_factor );
  vec4 texColor;
  if (u_mipmap_level.x == -1) texColor = texture2D( s_texColor, v_texcoord0 ); // Sample the texture w/auto-mipmap LOD
  else texColor = texture2DLod( s_texColor, v_texcoord0, u_mipmap_level.x ); // Sample the texture @specified LOD
  texColor *= v_color0;
  gl_FragColor = vec4(texColor.rgb * lighting, texColor.a);
}
