#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include <vector>

class VertexArray {
public:
    VertexArray(std::vector<float> vertices);
    ~VertexArray();
    void Draw();
private:
    unsigned int VAO;
    unsigned int VBO;
    int verticesSize;
};

#endif // VERTEXARRAY_H