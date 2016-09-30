#include "Shader.h"
#include <fstream>
Shader::Shader()
{
}

Shader::~Shader()
{
  glDetachShader(programID_, fragmentShaderID_);
  glDetachShader(programID_, vertexShaderID_);
  glDeleteProgram(programID_);
}

void Shader::Use()
{
  glUseProgram(programID_);
}

void Shader::Release()
{
  glUseProgram(0);
}

void Shader::Load(const std::string &vertexShaderSource, const std::string &fragmentShaderSource)
{
  vertexShaderID_ = LoadShader(vertexShaderSource, GL_VERTEX_SHADER);
  fragmentShaderID_ = LoadShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
  programID_ = glCreateProgram();
  glAttachShader(programID_, vertexShaderID_);
  glAttachShader(programID_, fragmentShaderID_);
  glLinkProgram(programID_);
  BindAttributes();
  GetAllUniformLocations();
}

void Shader::BindAttribute(const GLuint location, const std::string &name)
{
  glBindAttribLocation(programID_, location, name.c_str());
}

void Shader::LoadMatrix4f(GLuint location, const glm::mat4 & matrix4f)
{
  glUniformMatrix4fv(location, 1, GL_FALSE, &matrix4f[0][0]);
}

GLuint Shader::LoadShader(const std::string &shaderSource, const GLenum type)
{
  GLuint shaderID = glCreateShader(type);
  const char * const source = shaderSource.c_str();
  glShaderSource(shaderID, 1, &source, nullptr);
  glCompileShader(shaderID);
  std::ofstream file("D://log.txt");
  char buffer[1024];
  memset(buffer, 0, sizeof(buffer));
  glGetShaderInfoLog(shaderID, sizeof(buffer), nullptr, buffer);
  file << buffer << std::endl;
  file.close();
  return shaderID;
}
