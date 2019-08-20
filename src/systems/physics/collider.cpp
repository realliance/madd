#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "collider.h"
#include <limits>

Collider::Collider(std::vector<glm::vec3> collisionMesh):collisionMesh(collisionMesh),originalMesh(collisionMesh){
  colliderCenter = std::accumulate(std::begin(collisionMesh),std::end(collisionMesh),glm::vec3{})/static_cast<float>(collisionMesh.size());
}

const std::vector<glm::vec3>& Collider::getCollisionMesh(){
  return collisionMesh;
}

glm::vec3 Collider::getCenter(){
  return colliderCenter;
}

void Collider::updateModel(glm::mat4 model){
  collisionMesh = originalMesh;
  transform(begin(collisionMesh), end(collisionMesh), begin(collisionMesh),
    [&model](glm::vec3 v) -> glm::vec3 {
      return model * glm::vec4( v, 1.0 ); 
  });
  colliderCenter = std::accumulate(std::begin(collisionMesh),std::end(collisionMesh),glm::vec3{})/static_cast<float>(collisionMesh.size());
}

bool Collider::Collides(Collider& collider, int maxIteration){
  return collides(collider, *this, maxIteration);
}

glm::vec3 Collider::support(glm::vec3 dir){
  glm::vec3 dotpoint;
  float dotval = std::numeric_limits<float>::lowest();
  for(const auto& v : collisionMesh){
    float dot = glm::dot(v,dir);
    if(dot > dotval){
      dotval = dot;
      dotpoint = v;
    }
  }
  return dotpoint;
}

inline void print(glm::vec3 v, std::string s){
  std::cout << s << v.x << ", " << v.y << ", " << v.z << std::endl;
}

inline bool isZero(float n){
  return n < 1e-36 && n > -1e-36;
}

inline bool equal(float n0, float n1){
  return isZero(std::abs(n0-n1));
}

inline bool zeroVector(glm::vec3 v){
  return isZero(v.x) && isZero(v.y) && isZero(v.z);
}

inline bool zeroAxis(glm::vec3 p1, glm::vec3 p2){
  float d = (p1.x == 0 && p2.x == 0) ? -1 : p2.x / p1.x;
  return d <= 0 && equal(p1.y, p2.y / d) && equal(p1.z, p2.z / d);
}

bool Collider::collides(Collider& p, Collider& q, int maxIteration){
  glm::vec3 pc = p.getCenter();
  glm::vec3 qc = q.getCenter();

  glm::vec3 V0 = qc - pc;
  print(pc,"\npc: ");
  print(qc,"qc: ");
  print(V0,"V0: ");
  if(zeroVector(V0)){
    return true;
  }

  glm::vec3 n = -1.f * V0; 
  glm::vec3 V1 = q.support(n) - p.support(-n);

  if(zeroAxis(V0,V1)){
    return true;
  }
  
  n = cross(V1,V0);
  glm::vec3 V2 = q.support(n) - p.support(-n);
    
  n = cross(V1-V0,V2-V0);
  if(dot(n,V0) > 0){
    std::swap(V1,V2);
    n = -n;
  }

  print(V1,"V1: ");
  print(V2,"V2: ");

  glm::vec3 V3;
  for(int i = 0 ; i < maxIteration; i++){
    V3 = q.support(n) - p.support(-n);
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
      glm::vec3  V4 = q.support(n) - p.support(-n);
      float boundaryTolerance = 1e-20;
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
