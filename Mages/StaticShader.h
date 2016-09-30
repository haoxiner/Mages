#pragma once
#include "Shader.h"
#include "Camera.h"
class StaticShader : public Shader
{
public:
  StaticShader();
  ~StaticShader();
  void LoadModelMatrix(const glm::mat4 &matrix4f);
  void LoadViewMatrix(const Camera &camera);
  void LoadProjectionMatrix(const glm::mat4 &projectionMatrix);
protected:
  virtual void BindAttributes();
  virtual void GetAllUniformLocations();
private:
  GLuint modelLocation_;
  GLuint viewLocation_;
  GLuint projectionLocation_;
};

