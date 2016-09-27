#include "Entity.h"
Entity::Entity(const TexturedModel * model, const glm::vec3 & position, const glm::vec3 & rotation, const float scale)
  :model_(model), position_(position), rotation_(rotation), scale_(scale)
{
}

Entity::~Entity()
{
}

void Entity::Move(float dx, float dy, float dz)
{
  position_.x += dx;
  position_.y += dy;
  position_.z += dz;
}
