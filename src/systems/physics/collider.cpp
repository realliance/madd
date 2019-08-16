#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "collider.h"

Collider::Collider(std::vector<glm::vec3> collisionMesh):collisionMesh(collisionMesh){
  colliderCenter = std::accumulate(std::begin(collisionMesh),std::end(collisionMesh),glm::vec3{})/static_cast<float>(collisionMesh.size());
}

bool Collider::Collides(std::vector<glm::vec3>& collider, glm::vec3 pos, glm::mat4 model, glm::vec3 center, int maxIteration){
  std::transform(collider.begin(), collider.end(), collider.begin(),
    [&model](glm::vec3 v) -> glm::vec3 {
      return glm::vec4( v, 1.0 ) * model; 
  });
  return collides(collider, collisionMesh, center, maxIteration);
}

glm::vec3 Collider::support(std::vector<glm::vec3> points, glm::vec3 dir){
  glm::vec3 dotpoint;
  float dotval;
  for(const auto& v : points ){
    float dot = glm::dot(v,dir);
    if(dot > dotval){
      dotval = dot;
      dotpoint = v;
    }
  }
  return dotpoint;
}

bool Collider::collides(std::vector<glm::vec3>& p, std::vector<glm::vec3>& q, glm::vec3 pcenter, int maxIteration){
  glm::vec3 pc = pcenter;
  glm::vec3 qc = colliderCenter;
  glm::vec3 V0 = qc - pc;
  glm::vec3 n = -1.f * V0; 
  glm::vec3 V1 = support(q,n) - support(p, -n);
  
  n = cross(V1,V0);
  glm::vec3 V2 = support(q,n) - support(p, -n);
    
  n = cross(V1-V0,V2-V0);
  if(dot(n,V0) > 0){
    std::swap(V1,V2);
    n = -n;
  }

  glm::vec3 V3;
  for(int i = 0 ; i < maxIteration; i++){
    V3 = support(q,n) - support(p, -n);
    if(dot(V3, n) <= 0){
      return false;
    }
    if(dot(cross(V1,V3),V0) < 0){
      V2 = V3;
      n = cross(V1-V0,V3-V0);
      continue;
    }
    
    if (dot(cross(V3,V2),V0) < 0){
      V1 = V3;
      n = cross(V3-V0,V2-V0);
      continue;
    }
    break;
  }

  for(int i = 0 ; i < maxIteration; i++){
      n = cross(V2-V1,V3-V1);
      if(dot(n,V1) >= 0){
        return true;
      }
      glm::vec3  V4 = support(q,n) - support(p, -n);
      float boundaryTolerance = 0.000001f;
      if ( -dot(V4, n) >= 0 || dot(V4-V3,n) <= boundaryTolerance){
        return false;
      }

      glm::vec3 cross = glm::cross(V4,V0);
      if(dot(V1,cross) > 0){
        if(dot(V2,cross) > 0){
          V1 = V4;
        }else{
          V3 = V4;
        }
      }else{
        if(dot(V3,cross) > 0){
          V2 = V4;
        }else{
          V1 = V4;
        }
      }
    }
    std::cout << "maxIteration exceed" << std::endl;
    return false;
}
