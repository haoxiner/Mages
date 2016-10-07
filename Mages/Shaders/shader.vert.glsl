#version 400 core
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 bones[64];
in vec3 position;
in vec3 normal;
in vec2 texCoord;
in ivec4 boneIDs;
in vec4 boneWeights;
out vec3 v_position;
out vec3 v_normal;
out vec2 v_texCoord;
void main()
{
  mat4 boneTransform = bones[boneIDs[0]] * boneWeights[0];
  boneTransform += bones[boneIDs[1]] * boneWeights[1];
  boneTransform += bones[boneIDs[2]] * boneWeights[2];
  boneTransform += bones[boneIDs[3]] * boneWeights[3];

  vec4 positionInWorldSpace = model * boneTransform * vec4(position, 1.0);
  gl_Position = projection * view * positionInWorldSpace;
  v_texCoord = texCoord;
  v_normal = (model * boneTransform * vec4(normal, 0.0)).xyz;
  v_position = positionInWorldSpace.xyz;
}
