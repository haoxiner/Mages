#pragma once
#include "Entity.h"
class Player : public Entity
{
public:
  Player(const TexturedModel *model, const glm::vec3 &position, const glm::vec3 &rotation, const float scale);
  ~Player();
};

