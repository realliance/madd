#include "rendersystem.h"
#include "madd.h"
#include "camerasystem.h"
#include <glad/glad.h>
#include "shadersystem.h"
#include "meshsystem.h"
#include "texturesystem.h"
#include "instancerendersystem.h"
#include "glfwsystem.h"

void RenderSystem::Init() {
  shadersys = dynamic_cast<ShaderSystem*>(Madd::GetInstance().GetSystem("ShaderSystem"));
  meshsys = dynamic_cast<MeshSystem*>(Madd::GetInstance().GetSystem("MeshSystem"));
  texturesys = dynamic_cast<TextureSystem*>(Madd::GetInstance().GetSystem("TextureSystem"));
  instancerendersys = dynamic_cast<InstanceRenderSystem*>(Madd::GetInstance().GetSystem("InstanceRenderSystem"));
  glfwsys = dynamic_cast<GlfwSystem*>(Madd::GetInstance().GetSystem("GlfwSystem"));
  instanceSync = 0;
}

RenderSystem::~RenderSystem(){
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
  for(WindowComponent* w : glfwsys->GetWindows()){
    instanceSync = 1;
    if(instancerendersys == nullptr || instancerendersys->instanceSync == 0){
      Start(*w);
    }
    for(CameraComponent* c : w->cameras){
      for (RenderedComponent *r : objects) {
        updateComponent(*r,*c);
      }
    }
    if(instancerendersys == nullptr || instancerendersys->instanceSync == 1){
      instanceSync = 0;
      if(instancerendersys != nullptr){
        instancerendersys->instanceSync = 0;
      }
      Finish(*w);
    }
  }
}


void RenderSystem::updateComponent(RenderedComponent& r, CameraComponent& c){ 
  shadersys->Enable(*r.shader);
  shadersys->SetShade(*r.shader, &r.shade);
  shadersys->SetModel(*r.shader, &r.model);
  shadersys->SetView(*r.shader, &c.view);
  shadersys->SetProjection(*r.shader, &c.projection);
  shadersys->SetTime(*r.shader, Madd::GetInstance().GetTime());
  if(r.texture && texturesys != nullptr){
    shadersys->SetTextureEnabled(*r.shader, true);
    texturesys->Enable(r.texture);
  }else{
    shadersys->SetTextureEnabled(*r.shader,false);
  }
  meshsys->Draw(*r.mesh);
}

void RenderSystem::Start(WindowComponent& w){
  glfwsys->Enable(w);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::Finish(WindowComponent& w){
  glfwsys->Finish(w);
}
