#include <glad/glad.h>
#include "meshsystem.h"
#include "glfwsystem.h"
#include "madd.h"
#include <fstream>
#include <istream>
#include <sstream>
#include <set>

void MeshSystem::Init(){
  glfw = dynamic_cast<GlfwSystem*>(Madd::GetInstance().GetSystem("GlfwSystem"));
}

MeshSystem::~MeshSystem(){
  for(auto & [cid, mdata] : meshdata){
    destruct(mdata);
    delete mdata;
  }
}

bool MeshSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  MeshComponent* m = dynamic_cast<MeshComponent *>(component);
  MeshData* mdata = new MeshData{};
  mdata->mesh = m;
  m->data = mdata;
  meshdata[component->cID] = mdata;
  if(!initialize(meshdata[component->cID])){
    delete mdata;
    meshdata.erase(component->cID);
    return false;
  }  
  return true;
}

bool MeshSystem::Unregister(Component* component){
  if(meshdata.contains(component->cID)){
      destruct(meshdata[component->cID]);
      meshdata.erase(component->cID);
      return true;
  }
  return false;
}

void MeshSystem::destruct(MeshData* mdata) {
  if(GlfwSystem::GetCurrentWindow() != NULL){
    if(glfw != nullptr){
      glfw->DeleteComponentVAO(static_cast<Component*>(mdata->mesh));
    }
    glDeleteBuffers(1, &mdata->VBO[0]);
    glDeleteBuffers(1, &mdata->VBO[1]);
  }
}

bool MeshSystem::loadobj(MeshData* m){
  std::fstream obj("assets/" + m->mesh->modelPath, std::ios::in);

  if(!obj.is_open()){
    return false;
  }
  std::set<std::string> validtokens{"v","vt","f"};
  std::string line;
  std::vector<glm::vec3> iverts;
  std::vector<glm::vec2> itexs;
  while (std::getline(obj, line)){
    std::istringstream iss(line);
    std::string linetoken;
    if(!(iss >> linetoken)){ 
      break; 
    }
    if(!validtokens.contains(linetoken)){
      continue;
    }
    if(linetoken == "v"){
      float x,y,z;
      if (!(iss >> x >> y >> z)) { return false; }
      iverts.push_back({x,y,z});
    }
    if(linetoken == "vt"){
      float a,b;
      if (!(iss >> a >> b)) { return false; }
      itexs.push_back({a,b});
    }
    if(linetoken == "f"){
      char slash;
      int x[3],y[3],z[3];
      for(int i = 0; i < 3; i++){
        if (!(iss >> x[i] >> slash >> y[i] >> slash >> z[i])) { return false; }
        x[i]--; y[i]--; z[i]--; //objs use 1-indexed indices;
      }
      m->vertices.insert(end(m->vertices),{
        iverts[x[0]],iverts[x[1]],iverts[x[2]]
      });
      m->texcoords.insert(end(m->texcoords),{
        itexs[y[0]],itexs[y[1]],itexs[y[2]]
      });
    }
  }
  return true;
}

bool MeshSystem::initialize(MeshData* mdata) {
  if(!loadobj(mdata)){
    return false;
  }
  //Vertex Data  
  glGenBuffers(2, mdata->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, mdata->VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, mdata->vertices.size() * sizeof(glm::vec3),
              mdata->vertices.data(), GL_STATIC_DRAW);

  //Texture Data
  glBindBuffer(GL_ARRAY_BUFFER, mdata->VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, mdata->texcoords.size() * sizeof(glm::vec2),
              mdata->vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  return true;
}

uint MeshSystem::CreateVAO(Component* component){
  uint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO); 

  //Vertex Data
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, meshdata[component->cID]->VBO[0]);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);


  //Texture Data
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, meshdata[component->cID]->VBO[1]);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *)0);

  glBindVertexArray(0);
  return VAO;
}

void MeshSystem::Draw(MeshComponent& m){
  using namespace std::placeholders; 
  glBindVertexArray(glfw->GetCurrentContextVAO(static_cast<Component*>(&m),
    std::bind(&MeshSystem::CreateVAO, this, _1)));
  glDrawArrays(GL_TRIANGLES, 0, meshdata[m.cID]->vertices.size());
  glBindVertexArray(0);
}
