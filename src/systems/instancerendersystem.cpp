#include "instancerendersystem.h"
#include "madd.h"
#include "camerasystem.h"
#include <glad/glad.h>
#include "shadersystem.h"
#include "meshsystem.h"
#include "texturesystem.h"
#include "glfwsystem.h"
#include "rendersystem.h"

SystemType InstanceRenderSystem::sType = Madd::GetNewSystemType();

void InstanceRenderSystem::Init() {
  shadersys = Madd::GetInstance().GetSystem<ShaderSystem>();
  meshsys = Madd::GetInstance().GetSystem<MeshSystem>();
  texturesys = Madd::GetInstance().GetSystem<TextureSystem>();
  rendersys = Madd::GetInstance().GetSystem<RenderSystem>();
  glfwsys= Madd::GetInstance().GetSystem<GlfwSystem>();
  instanceSync = 0;
}

void InstanceRenderSystem::Deinit(){
    for(auto &[meshcID, inst] : instanceData){
      for(auto & cID : inst.cIDs){
        destruct(objects[cID]);
      }
    }
}

bool InstanceRenderSystem::Register(Component* component){
  InstanceRenderedComponent* rc = dynamic_cast<InstanceRenderedComponent*>(component);
  if(!instanceConfigs.contains(rc->mesh->cID)){
    return false;
  }
  rc->cID = Madd::GetInstance().GetNewComponentID();
  rc->update = true;
  objects[rc->cID] = dynamic_cast<InstanceRenderedComponent*>(component);
  InstanceDatum* inst;

  if(!instanceData.contains(rc->mesh->cID)){
    instanceData[rc->mesh->cID] = InstanceDatum{};
    inst = &instanceData[rc->mesh->cID];
    inst->config = instanceConfigs[rc->mesh->cID];;
    int nbuffers = 1;
    if(inst->config.instancedshade){
      nbuffers++;
    }else{
      shadersys->Enable(*(rc->shader));
      inst->shade = rc->shade;
      shadersys->SetShade(*(rc->shader), &inst->shade);
    }
    glGenBuffers(nbuffers, inst->VBO);
    inst->shader = rc->shader;
    inst->mesh = rc->mesh;

  }else{
    inst = &instanceData[rc->mesh->cID];
  }
  shadersys->Enable(*(rc->shader));
  shadersys->SetTextureEnabled(*(rc->shader),false);
  if(inst->config.simplemodel){
    inst->simplemodels.push_back(glm::vec3(rc->model[3]));
  }else{
    inst->models.push_back(rc->model);
  }
  if(inst->config.instancedshade){
    inst->shades.push_back(rc->shade);
  }
  inst->cIDs.push_back(component->cID);
  inst->rcs.push_back(rc);
  inst->update = true;
  return true;
}

void InstanceRenderSystem::SetConfig(InstanceConfig config, MeshComponent* mesh){
  instanceConfigs[mesh->cID] = config;
}

uint InstanceRenderSystem::CreateVAO(Component* component){
  MeshComponent* mesh = dynamic_cast<MeshComponent*>(component);
  uint VAO = meshsys->CreateVAO(mesh);
  InstanceDatum* inst = &instanceData[mesh->cID];
  glBindVertexArray(VAO);

  /*
    opengl only allows for 4 floats per vertex attrib so mat4 has 16 floats so
    it gets spread across 4 attribs.
  */
  if(inst->config.simplemodel){
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

  if(inst->config.instancedshade){
    //Shade Data
    glEnableVertexAttribArray(6);
    glBindBuffer(GL_ARRAY_BUFFER, instanceData[mesh->cID].VBO[1]);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), static_cast<void*>(0));

    glVertexAttribDivisor(6,1);
  }

  glBindVertexArray(0);
  return VAO;
}

bool InstanceRenderSystem::Unregister(Component* component){
  InstanceRenderedComponent* rc = dynamic_cast<InstanceRenderedComponent*>(component);
  objects.erase(rc->cID);
  InstanceDatum* inst = &instanceData[rc->mesh->cID];
  for(size_t i = 0; i < inst->models.size(); i++){
    if(inst->cIDs[i] == component->cID){
      if(inst->config.simplemodel){
        inst->simplemodels.erase(begin(inst->simplemodels)+i);
      }else{
        inst->models.erase(begin(inst->models)+i);
      }
      if(inst->config.instancedshade){
        inst->shades.erase(begin(inst->shades)+i);
      }
      inst->cIDs.erase(begin(inst->cIDs)+i);
      inst->rcs.erase(begin(inst->rcs)+i);
      inst->update = true;
      destruct(rc);
      if(inst->models.empty()){
        instanceData.erase(rc->mesh->cID);
      }
      return true;
    }
  }
  return false;
}

void InstanceRenderSystem::destruct(InstanceRenderedComponent* rc){
  if(Madd::GetInstance().IsInit<GlfwSystem>() == INITIALIZED){
    glDeleteBuffers(2, instanceData[rc->mesh->cID].VBO);
  }
}

void InstanceRenderSystem::Update(){
  for(WindowComponent* w : glfwsys->GetWindows()){
    instanceSync = 1;
    if(rendersys == nullptr || rendersys->instanceSync == 0){
      Start(*w);
    }
    for(CameraComponent* c : w->cameras){
      for(auto &[meshcID, inst] : instanceData){
        if(inst.config.updatemodel || inst.update){
          inst.update = false;
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
  if(inst.config.updatemodel && inst.update == false){
    for(size_t i = 0; i < inst.cIDs.size(); i++){
      if(inst.config.simplemodel){
        inst.simplemodels[i] = glm::vec3(inst.rcs[i]->model[3]);
      }else{
        inst.models[i] = inst.rcs[i]->model;
      }
      if(inst.config.instancedshade){
        inst.shades[i] = inst.rcs[i]->shade;
      }
    }
  }
  if(inst.config.simplemodel){
    glBindBuffer(GL_ARRAY_BUFFER,inst.VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, inst.simplemodels.size() * sizeof(glm::vec3),
      inst.simplemodels.data(), GL_STATIC_DRAW);
  }else{
    glBindBuffer(GL_ARRAY_BUFFER,inst.VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, inst.models.size() * sizeof(glm::mat4),
      inst.models.data(), GL_STATIC_DRAW);
  }

  if(inst.config.instancedshade){
    glBindBuffer(GL_ARRAY_BUFFER,inst.VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, inst.shades.size() * sizeof(glm::vec4),
      inst.shades.data(), GL_STATIC_DRAW);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InstanceRenderSystem::draw(InstanceDatum& inst, CameraComponent& c){
  shadersys->Enable(*inst.shader);
  shadersys->SetView(*inst.shader, &c.view);
  shadersys->SetProjection(*inst.shader, &c.projection);
  shadersys->SetTime(*inst.shader, Madd::GetInstance().GetTime());
  using namespace std::placeholders; 
  glBindVertexArray(glfwsys->GetCurrentContextVAO(static_cast<Component*>(inst.mesh),
    std::bind(&InstanceRenderSystem::CreateVAO, this, _1)));
  
  if(inst.config.simplemodel){
    meshsys->DrawInstanced(*inst.mesh, inst.simplemodels.size());
  }else{
    meshsys->DrawInstanced(*inst.mesh, inst.models.size());
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
