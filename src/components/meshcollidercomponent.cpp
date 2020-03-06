#include "meshcollidercomponent.h"
#include <numeric>
#include <algorithm>
#include "meshsystem.h"

glm::vec3 MeshColliderComponent::GetCenter(){
  return std::accumulate(
    std::begin(static_cast<MeshData*>(mesh->data)->vertices),
    std::end(static_cast<MeshData*>(mesh->data)->vertices),
    glm::vec3{},
    [this](glm::vec3 accum, glm::vec3 v) -> glm::vec3{
      return accum + static_cast<glm::vec3>(model * glm::vec4(v, 1.0f ));
    }
    )/static_cast<float>(static_cast<MeshData*>(mesh->data)->vertices.size());
}

glm::vec3 MeshColliderComponent::Support(glm::vec3 dir){
  glm::vec3 dotpoint;
  float dotval = std::numeric_limits<float>::lowest();
  for(const auto& v : static_cast<MeshData*>(mesh->data)->vertices){
    glm::vec3 transV = model * glm::vec4( v, 1.0f );
    float dot = glm::dot(transV,dir);
    if(dot > dotval){
      dotval = dot;
      dotpoint = transV;
    }
  }
  return dotpoint;
}
