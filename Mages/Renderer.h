#pragma once
#include "Entity.h"
#include "StaticShader.h"
#include <map>
#include <vector>
class Renderer
{
public:
  Renderer(StaticShader *staticShader);
  ~Renderer();
  void Prepare();
  void Render(Entity *entity);
  void Render(std::map<TexturedModel*, std::vector<Entity>> &entities);
  void PrepareTexturedModel(TexturedModel *model);
  void UnbindTexturedModel();
  void PrepareInstance(Entity &entity);
private:
  StaticShader *staticShader_;
};

