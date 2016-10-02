#include "MasterRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
MasterRenderer::MasterRenderer()
  :staticShader_(new StaticShader), terrainShader_(new TerrainShader)
{
  glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.01f, 10000.0f);
  entityRenderer_ = new EntityRenderer(staticShader_, projectionMatrix);
  terrainRenderer_ = new TerrainRenderer(terrainShader_, projectionMatrix);
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::Render(const PointLight & pointLight, const Camera & camera)
{
  staticShader_->Use();
  staticShader_->LoadViewMatrix(camera);
  entityRenderer_->Render(entities_);
  terrainRenderer_->Render(terrains_);
  staticShader_->Release();
  entities_.clear();
}

void MasterRenderer::ProcessEntity(const Entity & entity)
{
  entities_[entity.model_].push_back(&entity);
}

void MasterRenderer::ProcessTerrain(const Terrain & terrain)
{
  terrains_.push_back(&terrain);
}

void MasterRenderer::Prepare()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
