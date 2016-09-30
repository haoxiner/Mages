#pragma once
#include "OpenGLHeader.h"
class RawModel
{
public:
  RawModel(GLuint vaoID, int indicesCount);
  ~RawModel();
  const GLuint vaoID_;
  const unsigned indicesCount_;
};

