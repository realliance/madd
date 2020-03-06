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
  void Init();
  void Deinit(){}
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();

  std::vector<ComponentType> ComponentTypes() { return {RenderedComponent{}.Type()};}
  std::string Name(){ return "RenderSystem"; }
  SystemType Type() { return sType; }
  std::vector<std::string> Requires() {return {"GlfwSystem", "MeshSystem", "ShaderSystem"};};

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
  InstanceRenderSystem* instancerendersys;
  static SystemType sType;
};

