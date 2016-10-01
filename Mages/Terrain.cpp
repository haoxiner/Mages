#include "Terrain.h"

Terrain::Terrain(const float x, const float z, const ModelTexture * texture, Loader &loader)
  : x_(x), z_(z), texture_(texture), rawModel_(GenerateTerrain(loader))
{
}

Terrain::~Terrain()
{
}

RawModel *Terrain::GenerateTerrain(Loader &loader)
{
  int vertexCount = VERTEX_COUNT * VERTEX_COUNT;
  std::vector<float> vertices;
  std::vector<float> normals;
  std::vector<float> texCoords;
  std::vector<int> indices;
  for (int i = 0; i < VERTEX_COUNT; i++)
  {
    for (int j = 0; j < VERTEX_COUNT; j++)
    {
      vertices.push_back(((float)j / ((float)VERTEX_COUNT - 1.0f))*SIZE);
      vertices.push_back(0.0f);
      vertices.push_back(((float)i / ((float)VERTEX_COUNT - 1.0f))*SIZE);
      normals.push_back(0.0f);
      normals.push_back(1.0f);
      normals.push_back(0.0f);
      texCoords.push_back((float)j / ((float)VERTEX_COUNT - 1.0f));
      texCoords.push_back((float)i / ((float)VERTEX_COUNT - 1.0f));
    }
  }
  for (int gz = 0; gz < VERTEX_COUNT - 1; gz++)
  {
    for (int gx = 0; gx < VERTEX_COUNT - 1; gx++)
    {
      int topLeft = (gz * VERTEX_COUNT) + gx;
      int topRight = topLeft + 1;
      int bottomLeft = ((gz + 1) * VERTEX_COUNT + gx);
      int bottomRight = bottomLeft + 1;
      indices.push_back(topLeft);
      indices.push_back(bottomLeft);
      indices.push_back(topRight);
      indices.push_back(topRight);
      indices.push_back(bottomLeft);
      indices.push_back(bottomRight);
    }
  }
  return loader.LoadToVAO(vertices, normals, texCoords, indices);
}
