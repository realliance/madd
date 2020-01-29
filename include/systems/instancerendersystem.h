#pragma once

#include "system.h"
#include "components/instancedrenderedcomponent.h"
#include "components/cameracomponent.h"
#include "components/windowcomponent.h"
#include <unordered_map>

class Madd;
class ShaderSystem;
class MeshSystem;
class TextureSystem;

struct InstanceDatum {
  uint VBO[2]; //modelVBO, shadeVBO
  std::vector<ComponentID> cIDs;
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

  std::string Name(){ return "InstanceRenderSystem"; }
  std::vector<std::string> Requires() {return {"GlfwSystem", "MeshSystem", "ShaderSystem"};};

  void Start(WindowComponent& w);
  void Finish(WindowComponent& w);

  uint CreateVAO(Component* component);

  int instanceSync;
  
private:
  void updateInstance(InstanceDatum& inst);
  void draw(InstanceDatum& inst, CameraComponent& c);
  void destruct(InstancedRenderedComponent* rc);
  std::unordered_map<ComponentID,InstancedRenderedComponent*> objects;
  std::unordered_map<ComponentID, InstanceDatum> instanceData;
  
  ShaderSystem* shadersys;
  MeshSystem* meshsys;
  TextureSystem* texturesys;
  RenderSystem* rendersys;
  GlfwSystem* glfwsys;
};

