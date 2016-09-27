#pragma once
#include "RawModel.h"
#include <vector>
#include <string>
class Loader
{
public:
  Loader();
  ~Loader();
  RawModel* LoadToVAO(const std::vector<float> &vertices, const std::vector<unsigned> &indices);
  GLuint LoadTexture(const std::string &fileName);
private:
  GLuint CreateVAO();
  void UnbindVAO();
  void StoreDataInAttributeList(GLuint attributeLocation, const std::vector<float> &data);
  void BindIndicesBuffer(const std::vector<unsigned> &data);
  std::vector<GLuint> vaos_;
  std::vector<GLuint> vbos_;
  std::vector<GLuint> textures_;
};

