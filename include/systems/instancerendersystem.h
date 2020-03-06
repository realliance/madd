#pragma once

#include "system.h"
#include "components/instancerenderedcomponent.h"
#include "components/cameracomponent.h"
#include "components/windowcomponent.h"
#include <unordered_map>

class Madd;
class ShaderSystem;
class MeshSystem;
class TextureSystem;

struct InstanceConfig{
  // bool instancedtexture;
  bool instancedshade;
  bool simplemodel;
  bool updatemodel;
};

struct InstanceDatum {
  glm::vec4 shade;
  uint VBO[2]; //modelVBO, shadeVBO
  ShaderComponent* shader;
  MeshComponent* mesh;
  InstanceConfig config;
  bool update;
  std::vector<glm::mat4> models;
  std::vector<glm::vec3> simplemodels;
  std::vector<glm::vec4> shades;
  std::vector<ComponentID> cIDs;
  std::vector<InstanceRenderedComponent*> rcs;
};

class RenderSystem;
class GlfwSystem;
class InstanceRenderSystem : public System{
public:
  ~InstanceRenderSystem();
  void Init();
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();
  void SetConfig(InstanceConfig config, MeshComponent* mesh);

  std::vector<ComponentType> Types() { return {InstanceRenderedComponent{}.Type()};}
  std::string Name(){ return "InstanceRenderSystem"; }
  std::vector<std::string> Requires() {return {"GlfwSystem", "MeshSystem", "ShaderSystem"};};

  void Start(WindowComponent& w);
  void Finish(WindowComponent& w);

  uint CreateVAO(Component* component);

  int instanceSync;

private:
  void updateInstance(InstanceDatum& inst);
  void draw(InstanceDatum& inst, CameraComponent& c);
  void destruct(InstanceRenderedComponent* rc);
  std::unordered_map<ComponentID,InstanceRenderedComponent*> objects;
  std::unordered_map<ComponentID, InstanceDatum> instanceData;
  std::unordered_map<ComponentID, InstanceConfig> instanceConfigs;

  ShaderSystem* shadersys;
  MeshSystem* meshsys;
  TextureSystem* texturesys;
  RenderSystem* rendersys;
  GlfwSystem* glfwsys;
};

