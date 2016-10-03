#include "Player.h"

Player::Player(const TexturedModel *model, const glm::vec3 &position, const glm::vec3 &rotation, const float scale)
  :Entity(model, position, rotation, scale)
{
}

Player::~Player()
{
}
