#pragma once
#include "Terrain.h"
#include "TerrainShader.h"
#include <vector>
class TerrainRenderer
{
public:
  TerrainRenderer(TerrainShader *terrainShader, const glm::mat4 &projectionMatrix);
  ~TerrainRenderer();
  void Render(std::vector<const Terrain*> terrains);
private:
  void PrepareTerrain(const Terrain *terrain);
  void UnbindTexturedModel();
  TerrainShader *terrainShader_;
};

