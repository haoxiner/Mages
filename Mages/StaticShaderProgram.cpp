#include "StaticShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <sstream>
StaticShaderProgram::StaticShaderProgram()
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
  
  ShaderProgram::Load(vertexShaderSource, fragmentShaderSource);
}

StaticShaderProgram::~StaticShaderProgram()
{
}

void StaticShaderProgram::LoadModelMatrix(const glm::mat4 & matrix4f)
{
  LoadMatrix4f(modelLocation_, matrix4f);
}

void StaticShaderProgram::LoadViewMatrix(const Camera & camera)
{
  //glm::mat4 view = glm::lookAt(camera.position_, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

  /*
  * To make a matrix used to transform vector from world space to camera space
  * 1. makes the camera's position a new origin by minus camera.position
  * 2. performs inverse rotation by (-roll, -pitch, -yaw)
  */
  glm::mat4 view;
  view = glm::rotate(view, -camera.roll_, glm::vec3(1.0f, 0.0f, 0.0f));
  view = glm::rotate(view, -camera.pitch_, glm::vec3(0.0f, 1.0f, 0.0f));
  view = glm::rotate(view, -camera.yaw_, glm::vec3(0.0f, 0.0f, 1.0f));
  view = glm::translate(view, -camera.position_);
  
	glm::mat4 projection = glm::perspective(60.0f / 180.0f * 3.14f, 4.0f / 3.0f, 0.001f, 1000.0f);
	LoadMatrix4f(viewLocation_, view);
	LoadMatrix4f(projectionLocation_, projection);
}

void StaticShaderProgram::BindAttributes()
{
  ShaderProgram::BindAttribute(0, "position");
}

void StaticShaderProgram::GetAllUniformLocations()
{
  modelLocation_ = GetUniformLocation("model");
  viewLocation_ = GetUniformLocation("view");
  projectionLocation_ = GetUniformLocation("projection");
}