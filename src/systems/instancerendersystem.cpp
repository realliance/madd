#include "instancerendersystem.h"
#include "madd.h"
#include "camerasystem.h"
#include <glad/glad.h>
#include "shadersystem.h"
#include "meshsystem.h"
#include "texturesystem.h"
#include "glfwsystem.h"

void InstanceRenderSystem::Init() {
  shadersys = dynamic_cast<ShaderSystem*>(Madd::GetInstance().GetSystem("ShaderSystem"));
  meshsys = dynamic_cast<MeshSystem*>(Madd::GetInstance().GetSystem("MeshSystem"));
  texturesys = dynamic_cast<TextureSystem*>(Madd::GetInstance().GetSystem("TextureSystem"));

}

void InstanceRenderSystem::Deinit(){
}

bool InstanceRenderSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  objects.push_back(dynamic_cast<RenderedComponent*>(component));
  return true;
}



bool InstanceRenderSystem::Unregister(Component* component){
  for(auto i = begin(objects); i != end(objects); i++){
    if((*i)->cID == component->cID){
      objects.erase(i);
      return true;
    }
  }
  return false;
}

void InstanceRenderSystem::Update(){
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


void InstanceRenderSystem::updateComponent(RenderedComponent& r, CameraComponent& c){ 
  shadersys->Enable(*r.shader);
  shadersys->SetShade(*r.shader, &r.shade);
  shadersys->SetModel(*r.shader, &r.model);
  shadersys->SetView(*r.shader, &c.view);
  shadersys->SetProjection(*r.shader, &c.projection);
  shadersys->SetTime(*r.shader, Madd::GetInstance().GetTime());
  if(r.texture){
    shadersys->SetTextureEnabled(*r.shader, true);
    texturesys->Enable(r.texture);
  }else{
    shadersys->SetTextureEnabled(*r.shader,false);
  }
  meshsys->Draw(*r.mesh);
}

InstanceRenderSystem& InstanceRenderSystem::GetInstance() {

    static InstanceRenderSystem r;
    return r;
}


void InstanceRenderSystem::Start(WindowComponent& w){
  GlfwSystem* glfwsys= dynamic_cast<GlfwSystem*>(Madd::GetInstance().GetSystem("GlfwSystem"));
  glfwsys->Enable(w);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void InstanceRenderSystem::Finish(WindowComponent& w){
  GlfwSystem* glfwsys= dynamic_cast<GlfwSystem*>(Madd::GetInstance().GetSystem("GlfwSystem"));
  glfwsys->Finish(w);
}
