#include "Display.h"
#include "Loader.h"
#include "MasterRenderer.h"
#include "StaticShader.h"
#include "Entity.h"
#include "Camera.h"
#include "PointLight.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile("./Resources/Ganfaul_M_Aure.fbx", aiProcessPreset_TargetRealtime_Fast);
  aiMesh *mesh = scene->mMeshes[0];
  std::vector<float> vertices;
  std::vector<int> indices;
  for (int i = 0; i < mesh->mNumVertices; i++)
  {
    vertices.push_back(mesh->mVertices[i].x);
    vertices.push_back(mesh->mVertices[i].y);
    vertices.push_back(mesh->mVertices[i].z);
  }
  for (int i = 0; i < mesh->mNumFaces; i++)
  {
    indices.push_back(mesh->mFaces[i].mIndices[0]);
    indices.push_back(mesh->mFaces[i].mIndices[1]);
    indices.push_back(mesh->mFaces[i].mIndices[2]);
  }

	Loader loader;
	TexturedModel model(loader.LoadToVAO(vertices, indices), new ModelTexture(loader.LoadTexture("./Resources/123.DDS")));
  StaticShader staticShader;
  MasterRenderer renderer(&staticShader);
  std::default_random_engine randomEngine;
  std::uniform_real_distribution<float> uniformDistribution(0.0f, 1.0f);
  std::vector<Entity*> cubes;
  cubes.push_back(new Entity(
    &model,
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f), 1.0f));


  Camera camera;
  camera.position_ = glm::vec3(0.0f, 50.0f, 400.0f);
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