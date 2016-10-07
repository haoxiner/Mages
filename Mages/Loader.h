#pragma once
#include "RawModel.h"
#include <vector>
#include <string>
class Loader
{
public:
  Loader();
  ~Loader();
  RawModel* LoadToVAO(
    const std::vector<float> &vertices,
    const std::vector<float> &normals,
    const std::vector<float> &texCoords,
    const std::vector<int> &indices);
  RawModel* LoadToVAO(
    const std::vector<float> &vertices,
    const std::vector<float> &normals,
    const std::vector<float> &texCoords,
    const std::vector<int> &indices,
    const std::vector<int> &boneIDs,
    const std::vector<float> &boneWeights);
  GLuint LoadTexture(const std::string &fileName);
private:
  GLuint CreateVAO();
  void UnbindVAO();
  void StoreFloatDataInAttributeList(int attributeLocation, int numOfComponentsPerVertex, const std::vector<float> &data);
  void StoreIntDataInAttributeList(int attributeLocation, int numOfComponentsPerVertex, const std::vector<int> &data);
  void BindIndicesBuffer(const std::vector<int> &data);
  std::vector<GLuint> vaos_;
  std::vector<GLuint> vbos_;
  std::vector<GLuint> textures_;
};

