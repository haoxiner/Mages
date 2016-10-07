#ifdef TESTGAME
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
#include <sstream>
#include <random>
#include <queue>

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
  const aiScene *scene = importer.ReadFile("D:/GameDev/Resources/Akai_E_Espiritu.fbx", aiProcessPreset_TargetRealtime_Fast);

  Assimp::Importer animImporter;
  const aiScene *animScene = animImporter.ReadFile("D:/GameDev/Resources/standing_run_forward.fbx", aiProcessPreset_TargetRealtime_Fast);

  std::ofstream file("D:/model.log");
  
  
  file << "anim scene" << std::endl;
  file << animScene->mNumTextures << std::endl;
  file << animScene->mNumAnimations << std::endl;

  //for (int i = 0; i < scene->mNumTextures; i++)
  //{
  //  std::ostringstream ss;
  //  ss << i;
  //  std::string name("D:/textures/");
  //  name += ss.str();
  //  const char *bytes = reinterpret_cast<const char*>(scene->mTextures[i]->pcData);
  //  if (scene->mTextures[i]->CheckFormat("jpg"))
  //  {
  //    name += ".jpg";
  //  }

  //  if (scene->mTextures[i]->CheckFormat("png"))
  //  {
  //    name += ".png";
  //  }
  //  std::ofstream tf(name, std::ios::binary);
  //  if (scene->mTextures[i]->mHeight == 0)
  //  {
  //    tf.write(bytes, scene->mTextures[i]->mWidth);
  //  }
  //  tf.close();
  //}
  
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
    std::vector<int> boneIDs;
    std::vector<float> boneWeights;
    
    boneIDs.resize(4 * (vertices.size() / 3));
    boneWeights.resize(4 * (vertices.size() / 3));

    auto *boneMatrix = new std::vector<glm::mat4>;
    auto boneTransform = new std::vector<glm::mat4>;
    std::map<std::string, int> boneMap;
    for (int i = 0; i < mesh->mNumBones; i++)
    {
      boneMatrix->push_back(glm::mat4(mesh->mBones[i]->mOffsetMatrix[0][0]));
      boneTransform->push_back(glm::mat4());
      boneMap[std::string(mesh->mBones[i]->mName.C_Str())] = i;
      for (int j = 0; j < mesh->mBones[i]->mNumWeights; j++)
      {
        int vertexID = mesh->mBones[i]->mWeights[j].mVertexId;
        float weight = mesh->mBones[i]->mWeights[j].mWeight;
        for (int k = 0; k < 4; k++)
        {
          if (boneWeights[4 * vertexID + k] == 0.0f)
          {
            boneIDs[4 * vertexID + k] = i;
            boneWeights[4 * vertexID + k] = weight;
            break;
          }
        }
      }
    }
    file << std::endl << "NEWLINE" << std::endl;
    for (int i = 0; i < 16; i++)
    {
      file << sizeof(glm::mat4) / sizeof(float) << ",";
    }

    
    TexturedModel *model = new TexturedModel(loader.LoadToVAO(vertices, normals, texCoords, indices, boneIDs, boneWeights), texture);
    Entity *entity = new Entity(
      model,
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 0.0f, 0.0f), 0.01f);
    entity->bones_ = boneTransform;
    file << std::endl << entity->bones_->size();
    file.close();
    cubes.push_back(entity);

    /*
    file << meshIndex << ":" << std::endl;
    //mesh->mBones[0]->mWeights[0].mVertexId;
    
    // calculate max related bones per vertex
    std::map<int, int> countStatistic;
    for (int i = 0; i < mesh->mNumBones; i++)
    {
      for (int j = 0; j < mesh->mBones[i]->mNumWeights; j++)
      {
        if (countStatistic.find(mesh->mBones[i]->mWeights[j].mVertexId) != countStatistic.end())
        {
          countStatistic[mesh->mBones[i]->mWeights[j].mVertexId]++;
        }
        else
        {
          countStatistic[mesh->mBones[i]->mWeights[j].mVertexId] = 1;
        }
      }
    }
    int maxval = -1;
    for (auto p : countStatistic)
    {
      maxval = std::max(maxval, p.second);
    }
    file << "MAX BONES" << maxval << std::endl;

    file << "BONE total: " << mesh->mNumBones  << std::endl;
    for (int i = 0; i < mesh->mNumBones; i++)
    {
      file << mesh->mBones[i]->mName.C_Str() << ",";
    }
    */
  }
  /*
  file << "flag: ";
  file << scene->mAnimations[0]->mTicksPerSecond << std::endl;

  file << "ANIMATIONS" << std::endl;
  for (int i = 0; i < scene->mNumAnimations; i++)
  {
    for (int j = 0; j < scene->mAnimations[i]->mNumChannels; j++)
    {
      file << scene->mAnimations[i]->mChannels[j]->mNodeName.C_Str() << std::endl;
    }
  }
  

  file << std::endl << "TREE" << std::endl;
  std::queue<aiNode*> q;
  q.push(scene->mRootNode);
  file << scene->mRootNode->mName.C_Str() << std::endl;
  while (!q.empty())
  {
    aiNode *p = q.front();
    q.pop();
    for (int i = 0; i < p->mNumChildren; i++)
    {
      file << p->mChildren[i]->mName.C_Str() << std::endl;
      q.push(p->mChildren[i]);
    }
  }
 */


  std::map<std::string, aiNodeAnim*> keyFrameMap;
  
  for (int i = 0; i < animScene->mAnimations[0]->mNumChannels; i++)
  {
    keyFrameMap[std::string(animScene->mAnimations[0]->mChannels[i]->mNodeName.C_Str())] =
      animScene->mAnimations[0]->mChannels[i];
  }
  
  glm::mat4 world2RootBone(animScene->mRootNode->mTransformation[0][0]);
  glm::mat4 rootBone2World(glm::inverse(world2RootBone));
  auto q1 = new std::queue<aiNode*>;
  auto q2 = new std::queue<aiNode*>;
  auto q3 = q1;
  q1->push(animScene->mRootNode);
  glm::mat4 parentTransformation;
  while (!q1->empty())
  {
    auto node = q1->front();
    q1->pop();
    parentTransformation = node->mTransformation[0][0];


    for (int i = 0; i < node->mNumChildren; i++)
    {
      q2->push(node->mChildren[i]);
    }
    if (q1->empty())
    {
      q3 = q1;
      q1 = q2;
      q2 = q3;
    }
  }

  MasterRenderer renderer;
  //std::default_random_engine randomEngine;
  //std::uniform_real_distribution<float> uniformDistribution(0.0f, 1.0f);
  

  Camera camera;
  camera.position_ = glm::vec3(0.0f, 1.0f,1.9f);
  camera.roll_ = 0.0f;camera.pitch_ = 0.0f;camera.yaw_ = 0.0f;

  std::vector<Terrain*> terrains;
  ModelTexture *grass = new ModelTexture(loader.LoadTexture("D:/GameDev/Resources/grass.DDS"));
  terrains.push_back(new Terrain(0, 0, grass, loader));
  //terrains.push_back(new Terrain(-1, 0, grass, loader));
  
  PointLight pointLight;

  InputHandler inputHandler;
  inputHandler.SetKeyWPressedCommand(new MoveCameraForward(&camera));
  display.SetInputHandler(&inputHandler);

  /*return 0;*/
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
#endif