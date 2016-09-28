#pragma once
#include "Entity.h"
#include "StaticShader.h"
class Renderer
{
public:
  Renderer();
  ~Renderer();
  void Prepare();
  void Render(Entity *entity, StaticShader *staticShader);
};

