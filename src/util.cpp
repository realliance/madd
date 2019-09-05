#include "util.h"

#define x_v 0
#define y_v 1
#define z_v 2
glm::vec3 Util::VolumeCentroid(std::vector<float>& vertices, int stride){
  int length = vertices.size();
  glm::vec3 centroid = {0,0,0};
  for(int i = 0; i < length; i++){
      switch(i){
          case x_v:
              centroid[x_v] += vertices[i];
          break;
          case y_v:
              centroid[y_v] += vertices[i];
          break;
          case z_v:
              centroid[z_v] += vertices[i];
          break;
          default:
              i += stride-2;
      }
  }
  centroid[x_v] /= length/stride;
  centroid[y_v] /= length/stride;
  centroid[z_v] /= length/stride;
  return centroid;
}

glm::vec3 Util::MinBoundingBox(std::vector<float>& vertices, int stride, glm::vec3 centroid){
  glm::vec3 boundingBox;
  int length = vertices.size();
  for(int i = 0; i < length; i++){
      switch(i){
          case x_v:
              boundingBox[x_v] = vertices[i] < boundingBox[x_v] ? vertices[i] : boundingBox[x_v];
          break;
          case y_v:
              boundingBox[y_v] = vertices[i] < boundingBox[y_v] ? vertices[i] : boundingBox[y_v];
          break;
          case z_v:
              boundingBox[z_v] = vertices[i] < boundingBox[z_v] ? vertices[i] : boundingBox[z_v];
          break;
          default:
              i += stride-2;
      }
  }
  boundingBox[x_v] -= centroid[x_v];
  boundingBox[y_v] -= centroid[y_v];
  boundingBox[z_v] -= centroid[z_v];
  return centroid;
}

glm::vec3 Util::MaxBoundingBox(std::vector<float>& vertices, int stride, glm::vec3 centroid){
  glm::vec3 boundingBox;
  int length = vertices.size();
  for(int i = 0; i < length; i++){
      switch(i){
          case x_v:
              boundingBox[x_v] = vertices[i] > boundingBox[x_v] ? vertices[i] : boundingBox[x_v];
          break;
          case y_v:
              boundingBox[y_v] = vertices[i] > boundingBox[y_v] ? vertices[i] : boundingBox[y_v];
          break;
          case z_v:
              boundingBox[z_v] = vertices[i] > boundingBox[z_v] ? vertices[i] : boundingBox[z_v];
          break;
          default:
              i += stride-2;
      }
  }
  boundingBox[x_v] -= centroid[x_v];
  boundingBox[y_v] -= centroid[y_v];
  boundingBox[z_v] -= centroid[z_v];
  return centroid;
}

float Util::MaxRadius(std::vector<float>& vertices, int stride, glm::vec3 centroid){
  glm::vec3 temp;
  float max = 0;
  int length = vertices.size();
  for(int i = 0; i < length; i++){
    switch(i){
      case x_v:
          temp[x_v] = vertices[i] - centroid[x_v];
          temp[x_v] *= temp[x_v];
      break;
      case y_v:
          temp[y_v] = vertices[i] - centroid[y_v];
          temp[y_v] *= temp[y_v];

      break;
      case z_v:
          temp[z_v] = vertices[i] - centroid[z_v];
          temp[z_v] *= temp[z_v];
      break;
      default:
        if((temp[x_v]+temp[y_v]+temp[z_v]) > max){
          max = temp[x_v]+temp[y_v]+temp[z_v];
        }
        i += stride-2;
    }
  }
  return sqrt(max);
}

#undef x_v
#undef y_v
#undef z_v

