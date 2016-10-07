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

#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <fstream>
#include <sstream>
#include <random>
#include <queue>

glm::mat4 world2RootBone;
glm::mat4 rootBone2World;
std::vector<glm::mat4> *boneTransform;
std::map<std::string, int> boneMap;
std::vector<glm::mat4> *boneMatrix;
std::map<std::string, aiNodeAnim*> keyFrameMap;
void TraverseBoneTree(aiNode *node, glm::mat4 parentTransformation)
{
  aiNodeAnim *animNode = keyFrameMap[std::string(node->mName.C_Str())];
  glm::mat4 nodeTransformation;
  
  if (animNode)
  {
    aiVector3D scaling = animNode->mScalingKeys[0].mValue;
    glm::mat4 scaleTransformation(
      scaling.x, 0.0f, 0.0f, 0.0f,
      0.0f, scaling.y, 0.0f, 0.0f,
      0.0f, 0.0f, scaling.z, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f);

    aiQuaternion rotation = animNode->mRotationKeys[0].mValue;
    aiMatrix3x3 rotationMatrix(rotation.GetMatrix());
    glm::mat4 rotationTransformation(
      rotationMatrix[0][0], rotationMatrix[1][0], rotationMatrix[2][0], rotationMatrix[3][0],
      rotationMatrix[0][1], rotationMatrix[1][1], rotationMatrix[2][1], rotationMatrix[3][1],
      rotationMatrix[0][2], rotationMatrix[1][2], rotationMatrix[2][2], rotationMatrix[3][2],
      rotationMatrix[0][3], rotationMatrix[1][3], rotationMatrix[2][3], rotationMatrix[3][3]);

    aiVector3D translate = animNode->mPositionKeys[0].mValue;
    glm::mat4 translateTransformation(
      1.0f, 0.0f, 0.0f, translate.x,
      0.0f, 1.0f, 0.0f, translate.y,
      0.0f, 0.0f, 1.0f, translate.z,
      0.0f, 0.0f, 0.0f, 1.0f);
    nodeTransformation = translateTransformation * rotationTransformation * scaleTransformation;
  }
  nodeTransformation = world2RootBone;
  for (int i = 0; i < node->mNumChildren; i++)
  {
    TraverseBoneTree(node->mChildren[i], nodeTransformation);
  }
}

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

  Loader loader;
  ModelTexture *texture = new ModelTexture(loader.LoadTexture("D:/GameDev/Resources/grass.DDS"));

  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile("D:/GameDev/Resources/Akai_E_Espiritu.fbx", aiProcessPreset_TargetRealtime_Fast);

  Assimp::Importer animImporter;
  const aiScene *animScene = animImporter.ReadFile("D:/GameDev/Resources/standing_run_forward.fbx", aiProcessPreset_TargetRealtime_Fast);

  std::ofstream file("D:/model.log");

  int meshIndex = 0;
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
  boneMatrix = new std::vector<glm::mat4>;
  boneTransform = new std::vector<glm::mat4>;
  for (int i = 0; i < mesh->mNumBones; i++)
  {
    aiMatrix4x4 offset = mesh->mBones[i]->mOffsetMatrix;
    glm::mat4 offsetMatrix(
      offset[0][0], offset[1][0], offset[2][0], offset[3][0],
      offset[0][1], offset[1][1], offset[2][1], offset[3][1],
      offset[0][2], offset[1][2], offset[2][2], offset[3][2],
      offset[0][3], offset[1][3], offset[2][3], offset[3][3]);
    boneMatrix->push_back(offsetMatrix);


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

  TexturedModel *model = new TexturedModel(loader.LoadToVAO(vertices, normals, texCoords, indices, boneIDs, boneWeights), texture);
  Entity *entity = new Entity(
    model,
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f), 0.01f);
  entity->bones_ = boneTransform;
  file << std::endl << entity->bones_->size();
  file.close();

  

  for (int i = 0; i < animScene->mAnimations[0]->mNumChannels; i++)
  {
    keyFrameMap[std::string(animScene->mAnimations[0]->mChannels[i]->mNodeName.C_Str())] =
      animScene->mAnimations[0]->mChannels[i];
  }

  world2RootBone = glm::mat4(animScene->mRootNode->mTransformation[0][0]);
  rootBone2World = glm::mat4(glm::inverse(world2RootBone));
  auto q1 = new std::queue<aiNode*>;
  auto q2 = new std::queue<aiNode*>;
  auto q3 = q1;
  q1->push(animScene->mRootNode);
  glm::mat4 parentTransformation;


  MasterRenderer renderer;

  Camera camera;
  camera.position_ = glm::vec3(0.0f, 1.0f, 1.9f);
  camera.roll_ = 0.0f;camera.pitch_ = 0.0f;camera.yaw_ = 0.0f;

  std::vector<Terrain*> terrains;
  ModelTexture *grass = new ModelTexture(loader.LoadTexture("D:/GameDev/Resources/grass.DDS"));
  terrains.push_back(new Terrain(0, 0, grass, loader));

  PointLight pointLight;

  InputHandler inputHandler;
  inputHandler.SetKeyWPressedCommand(new MoveCameraForward(&camera));
  display.SetInputHandler(&inputHandler);

  /*return 0;*/
  while (display.IsRunning())
  {
    float delta = display.GetDelta();
    renderer.ProcessEntity(*entity);
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
