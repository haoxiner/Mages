#include "EntityRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
EntityRenderer::EntityRenderer(StaticShader *staticShader)
  :staticShader_(staticShader)
{
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

EntityRenderer::~EntityRenderer()
{
}

void EntityRenderer::Render(std::map<const TexturedModel*, std::vector<const Entity*>> &entities)
{
  for (auto pair : entities)
  {
    const TexturedModel *model = pair.first;
    PrepareTexturedModel(model);
    for (auto entity : pair.second)
    {
      PrepareInstance(*entity);
      glDrawElements(GL_TRIANGLES, model->rawModel_->indicesCount_, GL_UNSIGNED_INT, 0);
    }
    UnbindTexturedModel();
  }
}

void EntityRenderer::PrepareTexturedModel(const TexturedModel * model)
{
  const RawModel *rawModel = model->rawModel_;
  const ModelTexture *texture = model->modelTexture_;
  glBindVertexArray(rawModel->vaoID_);
  glEnableVertexAttribArray(0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture->textureID_);
}

void EntityRenderer::UnbindTexturedModel()
{
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}

void EntityRenderer::PrepareInstance(const Entity & entity)
{ 
  glm::mat4 m;
  m = glm::translate(m, entity.position_);
  m = glm::rotate(m, entity.rotation_.y, glm::vec3(0.0f, 1.0f, 0.0f));
  m = glm::rotate(m, entity.rotation_.x, glm::vec3(1.0f, 0.0f, 0.0f));
  staticShader_->LoadModelMatrix(m);
}
