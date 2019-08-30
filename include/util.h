#pragma once
#include <vector>
#include <glm/glm.hpp>

class Util{
  public:
    static glm::vec3 VolumeCentroid(std::vector<float>& vertices, int stride);
    static glm::vec3 MaxBoundingBox(std::vector<float>& vertices, int stride, glm::vec3 centroid);
    static glm::vec3 MinBoundingBox(std::vector<float>& vertices, int stride, glm::vec3 centroid);
    static float MaxRadius(std::vector<float>& vertices, int stride, glm::vec3 centroid);
};


