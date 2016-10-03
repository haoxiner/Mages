#include "Display.h"
#include "Loader.h"
#include "MasterRenderer.h"
#include "StaticShader.h"
#include "Entity.h"
#include "Camera.h"
#include "PointLight.h"
#include "InputHandler.h"
#include "MoveCameraForward.h"
#include "Player.h"

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

  std::vector<Entity*> cubes;
  Loader loader;
  ModelTexture *texture = new ModelTexture(loader.LoadTexture("D:/GameDev/Resources/grass.DDS"));

  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile("D:/GameDev/Resources/Paladin_w_Prop_J_Nordstrom.fbx", aiProcessPreset_TargetRealtime_Fast);

  std::ofstream file("D:/model.log");
  file << scene->mNumMeshes << std::endl;
  file.close();

  for (int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
  {
    aiMesh *mesh = scene->mMeshes[meshIndex];
    std::vector<float> vertices;
    std::vector<int> indices;
    std::vector<float> normals;
    std::vector<float> texCoords;

    for (int i = 0; i < mesh->mNumVertices; i++)
    {
      vertices.push_back(mesh->mVertices[i].x);
      vertices.push_back(mesh->mVertices[i].y);
      vertices.push_back(mesh->mVertices[i].z);

      normals.push_back(mesh->mNormals[i].x);
      normals.push_back(mesh->mNormals[i].y);
      normals.push_back(mesh->mNormals[i].z);

      texCoords.push_back(mesh->mTextureCoords[0][i].x);
      texCoords.push_back(mesh->mTextureCoords[0][i].y);
    }
    for (int i = 0; i < mesh->mNumFaces; i++)
    {
      indices.push_back(mesh->mFaces[i].mIndices[0]);
      indices.push_back(mesh->mFaces[i].mIndices[1]);
      indices.push_back(mesh->mFaces[i].mIndices[2]);
    }
    
    
    TexturedModel *model = new TexturedModel(loader.LoadToVAO(vertices, normals, texCoords, indices), texture);
    cubes.push_back(new Entity(
      model,
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 0.0f, 0.0f), 1.0f));
  }
  


  MasterRenderer renderer;
  //std::default_random_engine randomEngine;
  //std::uniform_real_distribution<float> uniformDistribution(0.0f, 1.0f);
  

  Camera camera;
  camera.position_ = glm::vec3(6.0f, 1.0f,45.9f);
  camera.roll_ = 0.0f;camera.pitch_ = 0.0f;camera.yaw_ = 0.0f;

  std::vector<Terrain*> terrains;
  ModelTexture *grass = new ModelTexture(loader.LoadTexture("D:/GameDev/Resources/grass.DDS"));
  terrains.push_back(new Terrain(0, 0, grass, loader));
  //terrains.push_back(new Terrain(-1, 0, grass, loader));
  
  PointLight pointLight;

  InputHandler inputHandler;
  inputHandler.SetKeyWPressedCommand(new MoveCameraForward(&camera));
  display.SetInputHandler(&inputHandler);


	while (display.IsRunning())
	{
    float delta = display.GetDelta();
    for (auto entity : cubes)
    {
      renderer.ProcessEntity(*entity);
    }
    for (auto terrain : terrains)
    {
      renderer.ProcessTerrain(*terrain);
    }
    renderer.Prepare();
    renderer.Render(pointLight, camera);
		display.Update();
	}
	display.Destroy();
	return 0;
}