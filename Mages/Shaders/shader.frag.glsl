#version 400 core
uniform sampler2D u_sampler;
in vec3 v_position;
in vec3 v_normal;
in vec2 v_texCoord;
out vec4 fragColor;
void main()
{
  float diffuse = max(0.0, dot(
    normalize(vec3(1000.0,1000.0,1000.0) - v_position),
    normalize(v_normal)));
  fragColor = vec4(pow(diffuse * texture(u_sampler, v_texCoord * vec2(40.0)).xyz, vec3(1.0/2.2)), 1.0);
}