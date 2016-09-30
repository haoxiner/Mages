#version 400 core
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
in vec3 position;
out vec2 v_texCoord;
void main()
{
  gl_Position = projection * view * model * vec4(position, 1.0);
  // gl_Position = model * vec4(position, 1.0);
  v_texCoord = position.xy;
}
