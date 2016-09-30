#version 400 core
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
in vec3 position;
in vec3 normal;
in vec2 texCoord;
out vec3 v_position;
out vec3 v_normal;
out vec2 v_texCoord;
void main()
{
  vec4 positionInWorldSpace = model * vec4(position, 1.0);
  gl_Position = projection * view * positionInWorldSpace;
  v_texCoord = texCoord;
  v_normal = (model * vec4(normal, 0.0)).xyz;
  v_position = positionInWorldSpace.xyz;
}
