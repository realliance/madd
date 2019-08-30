#pragma once
#include <vector>
#include "vertexarraycomponent.h"

class VertexArray {
public:
    VertexArray() = delete;
    static VertexArrayComponent Construct(std::vector<float> vertices);
    static void Destruct(VertexArrayComponent v);
    static void Draw(VertexArrayComponent v);
};

