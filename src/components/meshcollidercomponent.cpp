#include "meshcollidercomponent.h"
#include <numeric>
#include <algorithm>

glm::vec3 MeshColliderComponent::GetCenter(){
  return std::accumulate(
    std::begin(mesh->verts),
    std::end(mesh->verts),
    glm::vec3{},
    [this](glm::vec3 accum, glm::vec3 v) -> glm::vec3{
      return accum + static_cast<glm::vec3>(model * glm::vec4(v, 1.0f ));
    }
    )/static_cast<float>(mesh->verts.size());
}

glm::vec3 MeshColliderComponent::Support(glm::vec3 dir){
  glm::vec3 dotpoint;
  float dotval = std::numeric_limits<float>::lowest();
  for(const auto& v : mesh->verts){
    glm::vec3 transV = model * glm::vec4( v, 1.0f );
    float dot = glm::dot(transV,dir);
    if(dot > dotval){
      dotval = dot;
      dotpoint = transV;
    }
  }
  return dotpoint;
}

