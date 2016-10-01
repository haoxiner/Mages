#pragma once
#include "Terrain.h"
#include "StaticShader.h"
#include <vector>
class TerrainRenderer
{
public:
  TerrainRenderer(StaticShader *staticShader, const glm::mat4 &projectionMatrix);
  ~TerrainRenderer();
  void Render(std::vector<const Terrain*> terrains);
private:
  void PrepareTerrain(const Terrain *terrain);
  void UnbindTexturedModel();
  StaticShader *staticShader_;
};

