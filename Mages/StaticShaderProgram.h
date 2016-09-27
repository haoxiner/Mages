#pragma once
#include "ShaderProgram.h"
#include "Camera.h"
class StaticShaderProgram : public ShaderProgram
{
public:
  StaticShaderProgram();
  ~StaticShaderProgram();
  void LoadModelMatrix(const glm::mat4 &matrix4f);
  void LoadViewMatrix(const Camera &camera);
protected:
  virtual void BindAttributes();
  virtual void GetAllUniformLocations();
private:
  GLuint modelLocation_;
  GLuint viewLocation_;
  GLuint projectionLocation_;
};

