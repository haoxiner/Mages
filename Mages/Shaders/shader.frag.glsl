#version 400 core
uniform sampler2D u_sampler;
in vec2 v_texCoord;
out vec4 fragColor;
void main()
{
  fragColor = vec4(pow(texture(u_sampler, v_texCoord).xyz, vec3(1.0/2.2)), 1.0);
}