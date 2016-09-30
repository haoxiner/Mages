#include "Terrain.h"
RawModel *GenerateTerrain(Loader &loader);

Terrain::Terrain(const float x, const float z, const ModelTexture * texture, Loader &loader)
  : x_(x), z_(z), texture_(texture)
{
  rawModel_ = GenerateTerrain(loader);
}

Terrain::~Terrain()
{
}

RawModel *GenerateTerrain(Loader &loader)
{
  std::vector<float> vertices;
  std::vector<float> normals;
  std::vector<float> texCoords;
  std::vector<int> indices;
  return loader.LoadToVAO(vertices, normals, texCoords, indices);
}
