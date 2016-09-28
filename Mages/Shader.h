#pragma once
#include "OpenGLHeader.h"
#include <glm/glm.hpp>
#include <string>
class Shader
{
public:
  Shader();
  virtual ~Shader();
  void Use();
  void Release();
protected:
  virtual void BindAttributes() = 0;
  virtual void GetAllUniformLocations() = 0;
  void Load(
    const std::string &vertexShaderSource,
    const std::string &fragmentShaderSource);
  // bind attribute "name" to location
  void BindAttribute(const GLuint location, const std::string &name);
  GLuint GetUniformLocation(const std::string &name) const { return glGetUniformLocation(programID_, name.c_str()); }
  void LoadMatrix4f(GLuint location, const glm::mat4 &matrix4f);
private:
  // create and compile shader
  GLuint LoadShader(
    const std::string &shaderSource,
    const GLenum type);
  GLuint programID_;
  GLuint vertexShaderID_;
  GLuint fragmentShaderID_;
};

