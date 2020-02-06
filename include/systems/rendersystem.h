#pragma once

#include "system.h"
#include "components/renderedcomponent.h"
#include "components/cameracomponent.h"
#include "components/windowcomponent.h"

class Madd;
class ShaderSystem;
class MeshSystem;
class TextureSystem;
class InstanceRenderSystem;
class GlfwSystem;
class CameraSystem;
class RenderSystem : public System{
public:
  ~RenderSystem();
  void Init();
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();

  std::string Name(){ return "RenderSystem"; }
  std::vector<std::string> Requires() {return {"GlfwSystem", "MeshSystem", "ShaderSystem", "CameraSystem"};};

  void Start(WindowComponent& w);
  void Finish(WindowComponent& w);

  int instanceSync;
  
private:
  void updateComponent(RenderedComponent& r, CameraComponent& c);
  std::vector<RenderedComponent*> objects;
  ShaderSystem* shadersys;
  MeshSystem* meshsys;
  TextureSystem* texturesys;
  GlfwSystem* glfwsys;
  CameraSystem* camerasys;
  InstanceRenderSystem* instancerendersys;
};

