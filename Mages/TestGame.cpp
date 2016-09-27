#include "Display.h"
#include "Loader.h"
#include "Renderer.h"
#include "StaticShaderProgram.h"
#include "Entity.h"
#include "Camera.h"
#include <fstream>
int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow)
{
	Display display;
	if (!display.Initialize())
	{
		return -1;
	}
	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};
	std::vector<unsigned> indices = {
		0,1,2
	};
	Loader loader;
	TexturedModel model(loader.LoadToVAO(vertices, indices), new ModelTexture(loader.LoadTexture("./Resources/123.DDS")));
	Renderer renderer;
	renderer.Prepare();
	StaticShaderProgram shaderProgram;
	Entity entity(&model, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
  Camera camera;
  camera.position_ = glm::vec3(0.0f, 0.0f, 2.0f);
  camera.roll_ = 0.0f;camera.pitch_ = 0.0f;camera.yaw_ = 0.0f;

	while (display.IsRunning())
	{
		shaderProgram.Use();
    camera.pitch_ += 0.002f;
    shaderProgram.LoadViewMatrix(camera);
		renderer.Render(&entity, &shaderProgram);
		shaderProgram.Release();
		display.Update();
	}
	display.Destroy();
	return 0;
}