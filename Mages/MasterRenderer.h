#pragma once
#include "StaticShader.h"
#include "EntityRenderer.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "PointLight.h"
#include "Camera.h"
#include <map>
#include <vector>
class MasterRenderer
{
public:
  MasterRenderer(StaticShader *staticShader);
  ~MasterRenderer();
  void Render(const PointLight &pointLight, const Camera &camera);
  void ProcessEntity(const Entity &entity);
  void Prepare();
private:
  StaticShader *staticShader_;
  EntityRenderer *entityRenderer_;
  // entities to be rendered
  std::map<const TexturedModel*, std::vector<const Entity*>> entities_;
};

