#include "instancerendersystem.h"
#include "madd.h"
#include "camerasystem.h"
#include <glad/glad.h>
#include "shadersystem.h"
#include "meshsystem.h"
#include "texturesystem.h"
#include "glfwsystem.h"
#include "rendersystem.h"

void InstanceRenderSystem::Init() {
  shadersys = dynamic_cast<ShaderSystem*>(Madd::GetInstance().GetSystem("ShaderSystem"));
  meshsys = dynamic_cast<MeshSystem*>(Madd::GetInstance().GetSystem("MeshSystem"));
  texturesys = dynamic_cast<TextureSystem*>(Madd::GetInstance().GetSystem("TextureSystem"));
  rendersys = dynamic_cast<RenderSystem*>(Madd::GetInstance().GetSystem("RenderSystem"));
  glfwsys= dynamic_cast<GlfwSystem*>(Madd::GetInstance().GetSystem("GlfwSystem"));
  instanceSync = 0;
}

InstanceRenderSystem::~InstanceRenderSystem(){
    for(auto &[cID, inst] : instanceData){
        destruct(inst);
    }
}

bool InstanceRenderSystem::Register(Component* component){
  InstancedRenderedComponent* rc = dynamic_cast<InstancedRenderedComponent*>(component);
  rc->cID = Madd::GetInstance().GetNewComponentID();
  rc->update = true;

  instanceData[rc->cID] = InstanceDatum{};
  InstanceDatum* inst = &instanceData[rc->cID];
  int nbuffers = 1;
  if(rc->instancedshade){
    nbuffers++;
  }else{
    shadersys->Enable(*(rc->shader));
    shadersys->SetShade(*(rc->shader), &rc->shade);
  }
  glGenBuffers(nbuffers, inst->VBO);

  shadersys->Enable(*(rc->shader));
  shadersys->SetTextureEnabled(*(rc->shader),false);
  return true;
}

uint InstanceRenderSystem::CreateVAO(Component* component){
  InstancedRenderedComponent* irc = dynamic_cast<InstancedRenderedComponent*>(component);
  uint VAO = meshsys->CreateVAO(irc->mesh);
  InstanceDatum* inst = &instanceData[irc->cID];
  glBindVertexArray(VAO);

  /*
    opengl only allows for 4 floats per vertex attrib so mat4 has 16 floats so
    it gets spread across 4 attribs. The last attrib has a wilder stride to
    account for the id at the end of the structs.
  */
  if(inst->irc->positiononlymodels){
    //Model Data
    glBindBuffer(GL_ARRAY_BUFFER, inst->VBO[0]);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), static_cast<void*>(0));
    glVertexAttribDivisor(2,1);
  }else{
    size_t vec4size = sizeof(glm::vec4);
    //Model Data
    glBindBuffer(GL_ARRAY_BUFFER, inst->VBO[0]);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, vec4size*4, static_cast<void*>(0));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, vec4size*4, reinterpret_cast<void*>(vec4size));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, vec4size*4, reinterpret_cast<void*>(vec4size*2));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, vec4size*4, reinterpret_cast<void*>(vec4size*3));

    glVertexAttribDivisor(2,1);
    glVertexAttribDivisor(3,1);
    glVertexAttribDivisor(4,1);
    glVertexAttribDivisor(5,1);
  }

  if(irc->instancedshade){
    //Shade Data
    glEnableVertexAttribArray(6);
    glBindBuffer(GL_ARRAY_BUFFER, inst->VBO[1]);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), static_cast<void*>(0));

    glVertexAttribDivisor(6,1);
  }

  glBindVertexArray(0);
  return VAO;
}

bool InstanceRenderSystem::Unregister(Component* component){
  InstancedRenderedComponent* rc = dynamic_cast<InstancedRenderedComponent*>(component);
  destruct(instanceData[rc->cID]);
  instanceData.erase(rc->cID);
  return true;
}

void InstanceRenderSystem::destruct(InstanceDatum& inst){
  if(GlfwSystem::GetCurrentWindow() != NULL){
    glDeleteBuffers(2, inst.VBO);
  }
}

void InstanceRenderSystem::Update(){
  for(WindowComponent* w : glfwsys->GetWindows()){
    instanceSync = 1;
    if(rendersys == nullptr || rendersys->instanceSync == 0){
      Start(*w);
    }
    for(CameraComponent* c : w->cameras){
      for(auto &[cID, inst] : instanceData){
        if(inst.irc->update){
          updateInstance(inst);
        }
        draw(inst,*c);
      }
    }
    if(rendersys == nullptr || rendersys->instanceSync == 1){
      instanceSync = 0;
      if(rendersys != nullptr){
        rendersys->instanceSync = 0;
      }
      Finish(*w);
    }
  }
}

void InstanceRenderSystem::updateInstance(InstanceDatum& inst){
  if(inst.irc->positiononlymodels){
    glBindBuffer(GL_ARRAY_BUFFER,inst.VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, inst.irc->posmodels.size() * sizeof(glm::vec3),
      inst.irc->posmodels.data(), GL_STATIC_DRAW);
  }else{
    glBindBuffer(GL_ARRAY_BUFFER,inst.VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, inst.irc->models.size() * sizeof(glm::mat4),
      inst.irc->models.data(), GL_STATIC_DRAW);
  }

  if(inst.irc->instancedshade){
    glBindBuffer(GL_ARRAY_BUFFER,inst.VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, inst.irc->shades.size() * sizeof(glm::vec4),
      inst.irc->shades.data(), GL_STATIC_DRAW);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InstanceRenderSystem::draw(InstanceDatum& inst, CameraComponent& c){
  shadersys->Enable(*inst.irc->shader);
  shadersys->SetView(*inst.irc->shader, &c.view);
  shadersys->SetProjection(*inst.irc->shader, &c.projection);
  shadersys->SetTime(*inst.irc->shader, Madd::GetInstance().GetTime());
  using namespace std::placeholders; 
  glBindVertexArray(glfwsys->GetCurrentContextVAO(static_cast<Component*>(inst.irc),
    std::bind(&InstanceRenderSystem::CreateVAO, this, _1)));
  
  if(inst.irc->positiononlymodels){
    glDrawArraysInstanced(GL_TRIANGLES, 0, inst.irc->mesh->verts.size(), inst.irc->posmodels.size());
  }else{
    glDrawArraysInstanced(GL_TRIANGLES, 0, inst.irc->mesh->verts.size(), inst.irc->models.size());
  }
  glBindVertexArray(0);
}

void InstanceRenderSystem::Start(WindowComponent& w){
  glfwsys->Enable(w);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void InstanceRenderSystem::Finish(WindowComponent& w){
  glfwsys->Finish(w);
}
