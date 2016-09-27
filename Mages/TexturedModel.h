#pragma once
#include "RawModel.h"
#include "ModelTexture.h"
class TexturedModel
{
public:
  TexturedModel(const RawModel *rawModel, const ModelTexture *modelTexture);
  ~TexturedModel();
  const RawModel *rawModel_;
  const ModelTexture *modelTexture_;
};

