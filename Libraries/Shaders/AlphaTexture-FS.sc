$input v_color0, v_texcoord0

#include <bgfx_shader.sh>

uniform vec4 u_texture_size;

SAMPLER2D(s_texture,0);

void main()
{
  vec2 dx = dFdx( v_texcoord0 * u_texture_size.xy );
  vec2 dy = dFdy( v_texcoord0 * u_texture_size.xy );
  float mip_level = log2( max(length(dx), length(dy)) );
  vec4 texColor = texture2DLod( s_texture, v_texcoord0, mip_level );
  gl_FragColor = texColor * v_color0; // Output the texture color
}
