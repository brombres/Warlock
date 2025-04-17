$input v_color0, v_texcoord0, v_normal

#include <bgfx_shader.sh>

SAMPLER2D(s_texture,0);

void main()
{
  vec3  light_direction = vec3( 0.5774, 0.5774, -0.5774 );
  //vec3  light_direction = vec3( 0, 0, -1 );
  float light_factor = max( dot(v_normal,-light_direction), 0.0 );

  vec3 ambient  = vec3(0.4226,0.4226,0.4226);
  vec3 lighting = vec3( light_factor, light_factor, light_factor ) + ambient;

  // Based LOD on longest dimension, not shortest like texture2D()
  vec2 texture_size = bgfxTextureSize( s_texture, 0 );
  vec2 dx = dFdx( v_texcoord0 * texture_size );
  vec2 dy = dFdy( v_texcoord0 * texture_size );
  float mip_level = log2( min(length(dx), length(dy)) );
  vec4 texColor = texture2DLod( s_texture, v_texcoord0, mip_level );

  texColor *= v_color0;
  gl_FragColor = vec4(texColor.rgb * lighting, texColor.a);
}
