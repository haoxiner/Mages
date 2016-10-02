#pragma once
#include "Command.h"
class InputHandler
{
public:
  InputHandler();
  ~InputHandler();
  void HandleInput();
  void Pressed(int keyCode);
  void SetKeyWPressedCommand(Command *command) { keyW_ = command; }
private:
  Command *keyW_;
};

