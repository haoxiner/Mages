#pragma once
#include "Entity.h"
#include "StaticShaderProgram.h"
class Renderer
{
public:
  Renderer();
  ~Renderer();
  void Prepare();
  void Render(Entity *entity, StaticShaderProgram *staticShader);
};

