#pragma once
#include "ModelTexture.h"
#include "RawModel.h"
#include "Loader.h"
class Terrain
{
public:
  Terrain(const float x, const float z, const ModelTexture * texture, Loader &loader);
  ~Terrain();
private:
  static const int SIZE = 800;
  static const int VERTEX_COUNT = 128;
  const RawModel *rawModel_;
  const ModelTexture *texture_;
  const float x_;
  const float z_;
};

