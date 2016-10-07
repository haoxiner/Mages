#include "StaticShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <sstream>

StaticShader::StaticShader()
{
  std::ifstream vShaderFile("./Shaders/shader.vert.glsl");
  std::ostringstream vShaderStream;
  vShaderStream << vShaderFile.rdbuf();
  vShaderFile.close();
  std::string vertexShaderSource(vShaderStream.str());

  std::ifstream fShaderFile("./Shaders/shader.frag.glsl");
  std::ostringstream fShaderStream;
  fShaderStream << fShaderFile.rdbuf();
  fShaderFile.close();
  std::string fragmentShaderSource(fShaderStream.str());
  
  Load(vertexShaderSource, fragmentShaderSource);
}

StaticShader::~StaticShader()
{
}

void StaticShader::LoadModelMatrix(const glm::mat4 &matrix4f)
{
  LoadMatrix4f(modelLocation_, matrix4f);
}

void StaticShader::LoadViewMatrix(const Camera &camera)
{
  //glm::mat4 view = glm::lookAt(camera.position_, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

  /*
  * To make a matrix used to transform vector from world space to camera space
  * 1. makes the camera's position a new origin by minus camera.position
  * 2. performs an inverse rotation by Rotate(-pitch, -yaw, -roll)
  */
  glm::mat4 view;
  view = glm::rotate(view, glm::radians(-camera.roll_), glm::vec3(0.0f, 0.0f, 1.0f));
  view = glm::rotate(view, glm::radians(-camera.pitch_), glm::vec3(1.0f, 0.0f, 0.0f));
  view = glm::rotate(view, glm::radians(-camera.yaw_), glm::vec3(0.0f, 1.0f, 0.0f));
  view = glm::translate(view, -camera.position_);
  LoadMatrix4f(viewLocation_, view);
}

void StaticShader::LoadProjectionMatrix(const glm::mat4 &projectionMatrix)
{
  LoadMatrix4f(projectionLocation_, projectionMatrix);
}

void StaticShader::LoadBones(const std::vector<glm::mat4> &bones)
{
  glUniformMatrix4fv(bonesLocation_, bones.size(), GL_FALSE, &bones[0][0][0]);
}

void StaticShader::BindAttributes()
{
  BindAttribute(0, "position");
  BindAttribute(1, "normal");
  BindAttribute(2, "texCoord");
  BindAttribute(3, "boneIDs");
  BindAttribute(4, "boneWeights");
}

void StaticShader::GetAllUniformLocations()
{
  modelLocation_ = GetUniformLocation("model");
  viewLocation_ = GetUniformLocation("view");
  projectionLocation_ = GetUniformLocation("projection");
  bonesLocation_ = GetUniformLocation("bones");
}
