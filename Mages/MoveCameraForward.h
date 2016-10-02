#pragma once
#include "Command.h"
#include "Camera.h"
class MoveCameraForward : public Command
{
public:
  MoveCameraForward(Camera *camera);
  ~MoveCameraForward();
  virtual void Execute();
private:
  Camera *camera_;
};

