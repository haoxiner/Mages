#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
Renderer::Renderer(StaticShader *staticShader)
  :staticShader_(staticShader)
{
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

Renderer::~Renderer()
{
}

void Renderer::Prepare()
{
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(Entity *entity)
{
  const TexturedModel *model = entity->model_;
  const RawModel *rawModel = model->rawModel_;
  const ModelTexture *texture = model->modelTexture_;

  glBindVertexArray(rawModel->vaoID_);
  glEnableVertexAttribArray(0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture->textureID_);

  glm::mat4 m;
  m = glm::translate(m, entity->position_);
  m = glm::rotate(m, entity->rotation_.y, glm::vec3(0.0f, 1.0f, 0.0f));
  m = glm::rotate(m, entity->rotation_.x, glm::vec3(1.0f, 0.0f, 0.0f));
  staticShader_->LoadModelMatrix(m);
  glDrawElements(GL_TRIANGLES, rawModel->indicesCount_, GL_UNSIGNED_INT, (void*) 0);
  
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}

void Renderer::Render(std::map<TexturedModel*, std::vector<Entity>>& entities)
{
}

void Renderer::PrepareTexturedModel(TexturedModel * model)
{
}

void Renderer::UnbindTexturedModel()
{
}

void Renderer::PrepareInstance(Entity & entity)
{
}
