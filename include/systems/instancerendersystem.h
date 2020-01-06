#pragma once

#include "system.h"
#include "components/renderedcomponent.h"
#include "components/cameracomponent.h"
#include "components/windowcomponent.h"

class Madd;
class ShaderSystem;
class MeshSystem;
class TextureSystem;
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
  
  InstanceRenderSystem(const InstanceRenderSystem&) = delete;
  InstanceRenderSystem& operator=(const InstanceRenderSystem&) = delete;
private:
  void updateComponent(RenderedComponent& r, CameraComponent& c);
  InstanceRenderSystem() = default;
  std::vector<RenderedComponent*> objects;
  ShaderSystem* shadersys;
  MeshSystem* meshsys;
  TextureSystem* texturesys;
};

