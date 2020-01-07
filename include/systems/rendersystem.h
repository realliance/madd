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
class RenderSystem : public System{
public:
  static RenderSystem& GetInstance();
  void Deinit();
  void Init();
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();

  std::string Name(){ return "RenderSystem"; }
  std::vector<std::string> Requires() {return {"GlfwSystem", "TextureSystem", "MeshSystem", "ShaderSystem"};};

  void Start(WindowComponent& w);
  void Finish(WindowComponent& w);

  int instanceSync;
  
  RenderSystem(const RenderSystem&) = delete;
  RenderSystem& operator=(const RenderSystem&) = delete;
private:
  void updateComponent(RenderedComponent& r, CameraComponent& c);
  RenderSystem() = default;
  std::vector<RenderedComponent*> objects;
  ShaderSystem* shadersys;
  MeshSystem* meshsys;
  TextureSystem* texturesys;
  GlfwSystem* glfwsys;
  InstanceRenderSystem* instancerendersys;
};

