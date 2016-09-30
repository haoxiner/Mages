#include "Terrain.h"
//static const float SIZE = 800;
//static const float VERTEX_COUNT = 128;

Terrain::Terrain(const RawModel * rawModel, const ModelTexture * texture, const float x, const float z)
  :rawModel_(rawModel), texture_(texture), x_(x), z_(z)
{
}

Terrain::~Terrain()
{
}
