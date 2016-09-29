#include "Display.h"
#include "Loader.h"
#include "MasterRenderer.h"
#include "StaticShader.h"
#include "Entity.h"
#include "Camera.h"
#include "PointLight.h"
#include <fstream>
#include <random>
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
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f, 1.0f
	};
	std::vector<unsigned> indices = {
    0,1,2,3,0,4,5,0,6,3,6,0,0,2,4,5,1,0,2,1,5,7,6,3,6,7,5,7,3,4,7,4,2,7,2,5
	};
	Loader loader;
	TexturedModel model(loader.LoadToVAO(vertices, indices), new ModelTexture(loader.LoadTexture("./Resources/123.DDS")));
  StaticShader staticShader;
  MasterRenderer renderer(&staticShader);
  std::default_random_engine randomEngine;
  std::uniform_real_distribution<float> uniformDistribution(0.0f, 1.0f);
  std::vector<Entity*> cubes;
  for (int i = 0; i < 200; i++)
  {
    float x = uniformDistribution(randomEngine) * 100.0f - 50.0f;
    float y = uniformDistribution(randomEngine) * 100.0f - 50.0f;
    float z = uniformDistribution(randomEngine) * -300.0f;
    cubes.push_back(new Entity(
      &model,
      glm::vec3(x, y, z),
      glm::vec3(uniformDistribution(randomEngine) * 180.0f, uniformDistribution(randomEngine) * 180.0f, 0.0f), 1.0f));
  }
  Camera camera;
  camera.position_ = glm::vec3(0.0f, 0.0f, 5.0f);
  camera.roll_ = 0.0f;camera.pitch_ = 0.0f;camera.yaw_ = 0.0f;

  PointLight pointLight;
	while (display.IsRunning())
	{
    for (auto entity : cubes)
    {
      renderer.ProcessEntity(*entity);
    }
    renderer.Prepare();
    renderer.Render(pointLight, camera);
		display.Update();
	}
	display.Destroy();
	return 0;
}