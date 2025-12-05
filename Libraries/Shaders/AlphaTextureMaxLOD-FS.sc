$input v_color0, v_texcoord0

#include <bgfx_shader.sh>
#include "defs.sh"

SAMPLER2D(s_texture,0);

void main()
{
  // Base LOD on longest dimension, not shortest like texture2D()
  vec2 texture_size = vec2( textureSize( s_texture, 0 ) );
  vec2 dx = dFdx( v_texcoord0 * texture_size );
  vec2 dy = dFdy( v_texcoord0 * texture_size );
  float mip_level = log2( min(length(dx), length(dy)) );
  vec4 texColor = texture2DLod( s_texture, v_texcoord0, mip_level );

  //vec4 texColor = texture2D( s_texture, v_texcoord0 );

  gl_FragColor = texColor * v_color0;
}
