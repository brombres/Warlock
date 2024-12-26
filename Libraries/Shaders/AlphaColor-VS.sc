$input a_position, a_color0
$output v_color0

void main() {
  // Pass the vertex color to the fragment shader
  v_color0 = a_color0;

  // Set the clip space position of the vertex
  gl_Position = vec4(a_position, 1.0);
}
