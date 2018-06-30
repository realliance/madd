#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include <vector>

class VertexArray {
public:
    VertexArray(std::vector<float> vertices,
                std::vector<unsigned int> indices);
    ~VertexArray();
    void Draw();
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    int indicesSize;
};

#endif // VERTEXARRAY_H