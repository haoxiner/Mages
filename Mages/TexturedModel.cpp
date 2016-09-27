#include "TexturedModel.h"
TexturedModel::TexturedModel(const RawModel *rawModel, const ModelTexture *modelTexture)
  :rawModel_(rawModel), modelTexture_(modelTexture)
{
}

TexturedModel::~TexturedModel()
{
}
