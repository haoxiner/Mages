#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Prepare()
{
  glEnable(GL_DEPTH_BUFFER);
  glDepthFunc(GL_LESS);
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void Renderer::Render(Entity *entity, StaticShaderProgram *staticShader)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const TexturedModel *model = entity->model_;
  const RawModel *rawModel = model->rawModel_;
  const ModelTexture *texture = model->modelTexture_;

  glBindVertexArray(rawModel->vaoID_);
  glEnableVertexAttribArray(0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture->textureID_);

  entity->Move(0.0f, 0.0f, 0.0f);
  glm::mat4 m;
  m = glm::translate(m, entity->position_);
  staticShader->LoadModelMatrix(m);
  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDrawElements(GL_TRIANGLES, rawModel->indicesCount_, GL_UNSIGNED_INT, (void*) 0);
  //glDisable(GL_BLEND);
  
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}
