// Uniform to define the solid fill color (RGBA)
//uniform vec4 u_color;

$input v_color0

#include "bgfx_shader.sh"

void main() {
  // Multiply the uniform color by the vertex color
  //gl_FragColor = u_color * v_color0;
  gl_FragColor = v_color0;
}
