#pragma once
#include "Entity.h"
#include "StaticShader.h"
#include <map>
#include <vector>
class EntityRenderer
{
public:
  EntityRenderer(StaticShader *staticShader, const glm::mat4 &projectionMatrix);
  ~EntityRenderer();
  void Render(std::map<const TexturedModel*, std::vector<const Entity*>> &entities);
  void PrepareTexturedModel(const TexturedModel *model);
  void UnbindTexturedModel();
  void PrepareInstance(const Entity &entity);
private:
  StaticShader *staticShader_;
};

