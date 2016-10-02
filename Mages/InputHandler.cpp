#include "InputHandler.h"
#include "MoveCameraForward.h"
InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::HandleInput()
{
}

void InputHandler::Pressed(int keyCode)
{
  switch (keyCode)
  {
  case 'W':
    keyW_->Execute();
  default:
    break;
  }
}
