#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <glad/glad.h>
#include <vector>

class VertexArray {
public:
  VertexArray(std::vector<float> vertices, std::vector<unsigned int> indices, bool rgbcolor);
  ~VertexArray();
  void Bind();
  static void UnBind();

private:
  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;
};

#endif // VERTEXARRAY_H