#include "MasterRenderer.h"
MasterRenderer::MasterRenderer(StaticShader *staticShader)
  :staticShader_(staticShader), renderer_(new Renderer(staticShader))
{
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::Render(const PointLight & pointLight, const Camera & camera)
{
  staticShader_->Use();
  staticShader_->LoadViewMatrix(camera);
  renderer_->Prepare();
  renderer_->Render(entities_);
  staticShader_->Release();
  entities_.clear();
}

void MasterRenderer::ProcessEntity(const Entity & entity)
{
  entities_[entity.model_].push_back(&entity);
}
