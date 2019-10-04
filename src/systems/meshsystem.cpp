#include <glad/glad.h>
#include "meshsystem.h"
#include "glfwsystem.h"
#include "madd.h"

void MeshSystem::Init(){}

void MeshSystem::Deinit(){
    for(MeshComponent* m : mesh){
      destruct(*m);
    }
    delete this;
}

bool MeshSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  initialize(*dynamic_cast<MeshComponent *>(component));
  mesh.push_back(dynamic_cast<MeshComponent *>(component));
  return true;
}

bool MeshSystem::Unregister(Component* component){
  for (auto i = begin(mesh); i != end(mesh); i++) {
    if ((*i)->cID == component->cID) {
      destruct(**i);
      mesh.erase(i);
      return true;
    }
  }
  return false;
}

void MeshSystem::Update(){
  for(MeshComponent* m : mesh){
    if(m->update){
      destruct(*m);
      initialize(*m);
    }
  }
}

void MeshSystem::destruct(MeshComponent& m) {
  if(GlfwSystem::GetCurrentWindow() != NULL){
    glDeleteVertexArrays(1, &VAO[m.cID]);
    glDeleteBuffers(1, &VBO[m.cID][0]);
    glDeleteBuffers(1, &VBO[m.cID][1]);
    VAO.erase(m.cID);
    VBO.erase(m.cID);
  }
}

void MeshSystem::initialize(MeshComponent& m) {
  glGenVertexArrays(1, &VAO[m.cID]);
  glBindVertexArray(VAO[m.cID]); 

  //Vertex Data  
  glGenBuffers(2, VBO[m.cID]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[m.cID][0]);
  glBufferData(GL_ARRAY_BUFFER, m.verts.size() * sizeof(float),
              m.verts.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  //Texture Data
  glBindBuffer(GL_ARRAY_BUFFER, VBO[m.cID][1]);
  glBufferData(GL_ARRAY_BUFFER, m.texcoords.size() * sizeof(float),
              m.texcoords.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
void MeshSystem::Draw(MeshComponent& m){
    glBindVertexArray(VAO[m.cID]);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
