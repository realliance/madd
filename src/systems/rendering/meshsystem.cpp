#include <glad/glad.h>
#include "meshsystem.h"
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
    glDeleteVertexArrays(1, &m.VAO);
    glDeleteBuffers(1, &m.VBO);
}

void MeshSystem::initialize(MeshComponent& m) {
    glGenVertexArrays(1, &m.VAO);
    glGenBuffers(1, &m.VBO);

    glBindVertexArray(m.VAO); 

    glBindBuffer(GL_ARRAY_BUFFER, m.VBO);
    glBufferData(GL_ARRAY_BUFFER, m.vertices.size() * sizeof(float),
                m.vertices.data(), GL_STATIC_DRAW);
    
    //Vertex Data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    //Texture Data
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshSystem::Draw(MeshComponent& m){
    glBindVertexArray(m.VAO); 
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
