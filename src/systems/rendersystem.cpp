#include "rendersystem.h"
#include "madd.h"
#include "camerasystem.h"
#include <glad/glad.h>
#include "shadersystem.h"
#include "meshsystem.h"
#include "texturesystem.h"
#include "glfwsystem.h"

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
  GlfwSystem* glfwsys= dynamic_cast<GlfwSystem*>(Madd::GetInstance().GetSystem("GlfwSystem"));
  for(WindowComponent* w : glfwsys->GetWindows()){
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
  ShaderSystem* shadersys= dynamic_cast<ShaderSystem*>(Madd::GetInstance().GetSystem("ShaderSystem"));
  shadersys->Enable(*r.shader);
  shadersys->SetFloat4fUniform(shadersys->GetUniformLocation(*r.shader, "shade"), &r.shade);
  shadersys->SetMartix4fUniform(shadersys->GetUniformLocation(*r.shader, "model"), &r.model);
  shadersys->SetMartix4fUniform(shadersys->GetUniformLocation(*r.shader, "view"), &c.view);
  shadersys->SetMartix4fUniform(shadersys->GetUniformLocation(*r.shader, "projection"), &c.projection);
  shadersys->SetFloatUniform(shadersys->GetUniformLocation(*r.shader, "time"), Madd::GetInstance().GetTime());
  if(r.texture){
    shadersys->SetIntUniform(shadersys->GetUniformLocation(*r.shader, "textureEnabled"),1);
    dynamic_cast<TextureSystem*>(Madd::GetInstance().GetSystem("TextureSystem"))->Enable(r.texture);
  }else{
    shadersys->SetIntUniform(shadersys->GetUniformLocation(*r.shader, "textureEnabled"),0);
  }
  dynamic_cast<MeshSystem*>(Madd::GetInstance().GetSystem("MeshSystem"))->Draw(*r.mesh);
}

RenderSystem& RenderSystem::GetInstance() {

    static RenderSystem r;
    return r;
}


void RenderSystem::Start(WindowComponent& w){
  GlfwSystem* glfwsys= dynamic_cast<GlfwSystem*>(Madd::GetInstance().GetSystem("GlfwSystem"));
  glfwsys->Enable(w);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::Finish(WindowComponent& w){
  GlfwSystem* glfwsys= dynamic_cast<GlfwSystem*>(Madd::GetInstance().GetSystem("GlfwSystem"));
  glfwsys->Finish(w);
}
