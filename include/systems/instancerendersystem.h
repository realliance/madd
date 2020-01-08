#pragma once

#include "system.h"
#include "components/renderedcomponent.h"
#include "components/cameracomponent.h"
#include "components/windowcomponent.h"
#include <map>

class Madd;
class ShaderSystem;
class MeshSystem;
class TextureSystem;

struct instanceDatum {
  std::vector<glm::mat4> models;
  std::vector<glm::vec4> shades;
  std::vector<ComponentID> cIDs;
  uint VBO[2]; //modelVBO, shadeVBO
  ShaderComponent* shader;
  MeshComponent* mesh;
};

class RenderSystem;
class GlfwSystem;
class InstanceRenderSystem : public System{
public:
  static InstanceRenderSystem& GetInstance();
  void Deinit();
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
  
  InstanceRenderSystem(const InstanceRenderSystem&) = delete;
  InstanceRenderSystem& operator=(const InstanceRenderSystem&) = delete;
private:
  void updateInstance(instanceDatum& inst, CameraComponent& c);
  InstanceRenderSystem() = default;
  std::map<ComponentID,RenderedComponent*> objects;
  std::map<ComponentID, instanceDatum> instanceData;
  
  ShaderSystem* shadersys;
  MeshSystem* meshsys;
  TextureSystem* texturesys;
  RenderSystem* rendersys;
  GlfwSystem* glfwsys;
};

