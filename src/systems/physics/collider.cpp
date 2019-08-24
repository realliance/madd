#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "collider.h"
#include <limits>

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

bool Collider::Collides(ColliderComponent& p, ColliderComponent& q, int maxIteration){
  glm::vec3 pc = p.GetCenter();
  glm::vec3 qc = q.GetCenter();

  glm::vec3 V0 = qc - pc;
  if(zeroVector(V0)){
    return true;
  }

  glm::vec3 n = -1.f * V0; 
  glm::vec3 V1 = q.Support(n) - p.Support(-n);

  if(zeroAxis(V0,V1)){
    return true;
  }
  
  n = cross(V1,V0);
  glm::vec3 V2 = q.Support(n) - p.Support(-n);
    
  n = cross(V1-V0,V2-V0);
  if(dot(n,V0) > 0){
    std::swap(V1,V2);
    n = -n;
  }


  glm::vec3 V3;
  for(int i = 0 ; i < maxIteration; i++){
    V3 = q.Support(n) - p.Support(-n);
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
      glm::vec3  V4 = q.Support(n) - p.Support(-n);
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
