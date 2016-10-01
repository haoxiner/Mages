#include "TerrainRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
TerrainRenderer::TerrainRenderer(StaticShader *staticShader, const glm::mat4 &projectionMatrix)
  :staticShader_(staticShader)
{
  staticShader_->Use();
  staticShader_->LoadProjectionMatrix(projectionMatrix);
  staticShader_->Release();
}

TerrainRenderer::~TerrainRenderer()
{
}

void TerrainRenderer::Render(std::vector<const Terrain*> terrains)
{
  for (auto terrain : terrains)
  {
    PrepareTerrain(terrain);
    glm::mat4 m;
    m = glm::translate(m, glm::vec3(terrain->x_, 0.0f, terrain->z_));
    staticShader_->LoadModelMatrix(m);
    glDrawElements(GL_TRIANGLES, terrain->rawModel_->indicesCount_, GL_UNSIGNED_INT, 0);
    UnbindTexturedModel();
  }
}

void TerrainRenderer::PrepareTerrain(const Terrain * terrain)
{
  const RawModel *rawModel = terrain->rawModel_;
  const ModelTexture *texture = terrain->texture_;
  glBindVertexArray(rawModel->vaoID_);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture->textureID_);
}

void TerrainRenderer::UnbindTexturedModel()
{
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindVertexArray(0);
}
