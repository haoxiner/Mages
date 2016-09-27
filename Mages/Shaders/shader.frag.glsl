#version 400 core
uniform sampler2D u_sampler;
in vec2 v_texCoord;
out vec4 fragColor;
void main()
{
  fragColor = texture(u_sampler, v_texCoord);
  // fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}