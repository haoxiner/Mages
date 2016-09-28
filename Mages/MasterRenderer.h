#pragma once
#include "StaticShader.h"
#include "Renderer.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "PointLight.h"
#include "Camera.h"
#include <map>
#include <vector>
class MasterRenderer
{
public:
  MasterRenderer();
  ~MasterRenderer();
  void Render(const PointLight &pointLight, const Camera &camera);
private:
  StaticShader *staticShader_;
  Renderer *renderer_;
  std::map<TexturedModel*, std::vector<Entity*>> entities_;
};

