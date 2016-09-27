#include "Display.h"
Display::Display()
  :window_(nullptr), running_(false)
{
}

Display::~Display()
{
}

bool Display::Initialize()
{
  if (!glfwInit())
  {
    return false;
  }
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  window_ = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window_)
  {
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(window_);
  glewExperimental = true;
  if (glewInit() != GLEW_OK)
  {
    glfwTerminate();
    return false;
  }
  running_ = true;
  return true;
}

void Display::Update()
{
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

void Display::Destroy()
{
  glfwTerminate();
  window_ = nullptr;
  running_ = false;
}
