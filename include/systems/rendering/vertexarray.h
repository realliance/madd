#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include <vector>
#include "vertexarraycomponent.h"

class VertexArray {
public:
    VertexArray() = delete;
    static VertexArrayComponent Construct(std::vector<float> vertices);
    static void Destruct(VertexArrayComponent v);
    static void Draw(VertexArrayComponent v);
};

#endif // VERTEXARRAY_H
