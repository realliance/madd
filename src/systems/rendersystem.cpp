#include "rendersystem.h"
#include "madd.h"
#include "camerasystem.h"
#include <iostream>
#include <glad/glad.h>
#include "shadersystem.h"
#include "meshsystem.h"
#include "texturesystem.h"
#include "windowsystem.h"

void RenderSystem::Init() {
}

void RenderSystem::Deinit(){
}

bool RenderSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  objects.push_back(dynamic_cast<RenderedComponent*>(component));
  return true;
}



bool RenderSystem::Unregister(Component* component){
  for(auto i = begin(objects); i != end(objects); i++){
    if((*i)->cID == component->cID){
      objects.erase(i);
      return true;
    }
  }
  return false;
}

void RenderSystem::Update(){
  
  WindowSystem* windowsys= dynamic_cast<WindowSystem*>(Madd::GetInstance().GetSystem("WindowSystem"));
  for(WindowComponent* w : windowsys->GetWindows()){
    Start(*w);
    for(CameraComponent* c : w->cameras){
      for (RenderedComponent *r : objects) {
        updateComponent(*r,*c);
      }
    }
    Finish(*w);
  }
  
}


void RenderSystem::updateComponent(RenderedComponent& r, CameraComponent& c){
  ShaderSystem::Enable(*r.shader);
  ShaderSystem::SetFloat4fUniform(ShaderSystem::GetUniformLocation(*r.shader, "shade"), &r.shade);
  ShaderSystem::SetMartix4fUniform(ShaderSystem::GetUniformLocation(*r.shader, "model"), &r.model);
  ShaderSystem::SetMartix4fUniform(ShaderSystem::GetUniformLocation(*r.shader, "view"), &c.view);
  ShaderSystem::SetMartix4fUniform(ShaderSystem::GetUniformLocation(*r.shader, "projection"), &c.projection);
  ShaderSystem::SetFloatUniform(ShaderSystem::GetUniformLocation(*r.shader, "time"), Madd::GetInstance().GetTime());
  if(r.texture){
    ShaderSystem::SetIntUniform(ShaderSystem::GetUniformLocation(*r.shader, "textureEnabled"),1);
    TextureSystem::Enable(r.texture);
  }else{
    ShaderSystem::SetIntUniform(ShaderSystem::GetUniformLocation(*r.shader, "textureEnabled"),0);
  }

  MeshSystem::Draw(*r.mesh);
}

RenderSystem& RenderSystem::GetInstance() {

    static RenderSystem r;
    return r;
}


void RenderSystem::Start(WindowComponent& w){
  WindowSystem::Enable(w);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::Finish(WindowComponent& w){
  WindowSystem::Finish(w);
}
