#include "Loader.h"
#include <algorithm>
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

Loader::Loader()
{
}

Loader::~Loader()
{
}

RawModel *Loader::LoadToVAO(
  const std::vector<float> &vertices,
  const std::vector<float> &normals,
  const std::vector<float> &texCoords,
  const std::vector<int> &indices)
{
  GLuint vaoID = CreateVAO();
  StoreFloatDataInAttributeList(0, 3, vertices);
  StoreFloatDataInAttributeList(1, 3, normals);
  StoreFloatDataInAttributeList(2, 2, texCoords);
  BindIndicesBuffer(indices);
  UnbindVAO();
  return new RawModel(vaoID, indices.size());
}

RawModel * Loader::LoadToVAO(const std::vector<float>& vertices, const std::vector<float>& normals, const std::vector<float>& texCoords, const std::vector<int>& indices, const std::vector<int>& boneIDs, const std::vector<float>& boneWeights)
{
  GLuint vaoID = CreateVAO();
  StoreFloatDataInAttributeList(0, 3, vertices);
  StoreFloatDataInAttributeList(1, 3, normals);
  StoreFloatDataInAttributeList(2, 2, texCoords);
  StoreIntDataInAttributeList(3, 4, boneIDs);
  StoreFloatDataInAttributeList(4, 4, boneWeights);
  BindIndicesBuffer(indices);
  UnbindVAO();
  return new RawModel(vaoID, indices.size());
}

GLuint Loader::LoadTexture(const std::string & fileName)
{
  unsigned char header[124];
  FILE *fp = fopen(fileName.c_str(), "rb");
  if (fp == NULL)
  {
    return 0;
  }
  char filecode[4];
  fread(filecode, 1, 4, fp);
  if (strncmp(filecode, "DDS ", 4) != 0)
  {
    fclose(fp);
    return 0;
  }
  fread(&header, 124, 1, fp);
  unsigned int height = *(unsigned int*)&(header[8]);
  unsigned int width = *(unsigned int*)&(header[12]);
  unsigned int linearSize = *(unsigned int*)&(header[16]);
  unsigned int mipMapCount = *(unsigned int*)&(header[24]);
  unsigned int fourCC = *(unsigned int*)&(header[80]);
  unsigned char * buffer;
  unsigned int bufsize;
  /* how big is it going to be including all mipmaps? */
  bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
  buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
  fread(buffer, 1, bufsize, fp);
  /* close the file pointer */
  fclose(fp);
  unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
  unsigned int format;
  switch (fourCC)
  {
  case FOURCC_DXT1:
    format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
    break;
  case FOURCC_DXT3:
    format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
    break;
  case FOURCC_DXT5:
    format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
    break;
  default:
    free(buffer);
    return 0;
  }
  // Create one OpenGL texture
  GLuint textureID;
  glGenTextures(1, &textureID);
  textures_.push_back(textureID);

  // "Bind" the newly created texture : all future texture functions will modify this texture
  glBindTexture(GL_TEXTURE_2D, textureID);
  unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
  unsigned int offset = 0;

  /* load the mipmaps */
  for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
  {
    unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
    glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
      0, size, buffer + offset);

    offset += size;
    width = std::max(1u, width / 2u);
    height = std::max(1u, height / 2u);
  }
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipMapCount - 1);
  free(buffer);
  glBindTexture(GL_TEXTURE_2D, 0);
  return textureID;
}

GLuint Loader::CreateVAO()
{
  GLuint vaoID;
  glCreateVertexArrays(1, &vaoID);
  vaos_.push_back(vaoID);
  glBindVertexArray(vaoID);
  return vaoID;
}

void Loader::UnbindVAO()
{
  glBindVertexArray(0);
}

void Loader::StoreFloatDataInAttributeList(int attributeLocation, int numOfComponentsPerVertex, const std::vector<float> &data)
{
  GLuint vboID;
  glGenBuffers(1, &vboID);
  vbos_.push_back(vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(data[0]) * data.size(), &data[0], GL_STATIC_DRAW);
  glVertexAttribPointer(attributeLocation, numOfComponentsPerVertex, GL_FLOAT, GL_FALSE, 0, (const void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::StoreIntDataInAttributeList(int attributeLocation, int numOfComponentsPerVertex, const std::vector<int> &data)
{
  GLuint vboID;
  glGenBuffers(1, &vboID);
  vbos_.push_back(vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(data[0]) * data.size(), &data[0], GL_STATIC_DRAW);
  glVertexAttribIPointer(attributeLocation, numOfComponentsPerVertex, GL_INT, 0, (const void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::BindIndicesBuffer(const std::vector<int> &data)
{
  GLuint vboID;
  glGenBuffers(1, &vboID);
  vbos_.push_back(vboID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data[0]) * data.size(), &data[0], GL_STATIC_DRAW);
}
