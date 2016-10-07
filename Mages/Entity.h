#pragma once
#include "TexturedModel.h"
#include <glm/glm.hpp>
#include <vector>
class Entity
{
public:
  Entity(const TexturedModel *model, const glm::vec3 &position, const glm::vec3 &rotation, const float scale);
  ~Entity();
  void Move(float dx, float dy, float dz);
  const TexturedModel *model_;
  glm::vec3 position_;
  glm::vec3 rotation_;
  float scale_;
  std::vector<glm::mat4> *bones_;
};

