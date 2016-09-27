#pragma once
#include "OpenGLHeader.h"
class ModelTexture
{
public:
  ModelTexture(const GLuint textureID);
  ~ModelTexture();
  const GLuint textureID_;
};

