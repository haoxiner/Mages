#include "MoveCameraForward.h"

MoveCameraForward::MoveCameraForward(Camera *camera)
  :camera_(camera)
{
}

MoveCameraForward::~MoveCameraForward()
{
}

void MoveCameraForward::Execute()
{
  camera_->position_.z -= 0.1f;
}
