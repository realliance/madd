#pragma once

#include "system.h"
#include "components/renderedcomponent.h"
#include "components/cameracomponent.h"
#include "components/windowcomponent.h"
#include <unordered_map>

class Madd;
class ShaderSystem;
class MeshSystem;
class TextureSystem;

struct instanceDatum {
  std::vector<glm::mat4> models;
  std::vector<glm::vec4> shades;
  std::vector<ComponentID> cIDs;
  std::vector<RenderedComponent*> rcs;
  uint VBO[2]; //modelVBO, shadeVBO
  ShaderComponent* shader;
  MeshComponent* mesh;
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
  std::vector<std::string> Requires() {return {"GlfwSystem", "TextureSystem", "MeshSystem", "ShaderSystem"};};

  void Start(WindowComponent& w);
  void Finish(WindowComponent& w);

  uint CreateVAO(Component* component);

  int instanceSync;
  
private:
  void updateInstance(instanceDatum& inst, CameraComponent& c);
  void destruct(RenderedComponent* rc);
  std::unordered_map<ComponentID,RenderedComponent*> objects;
  std::unordered_map<ComponentID, instanceDatum> instanceData;
  
  ShaderSystem* shadersys;
  MeshSystem* meshsys;
  TextureSystem* texturesys;
  RenderSystem* rendersys;
  GlfwSystem* glfwsys;
};

