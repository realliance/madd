#include <glad/glad.h>
#include "vertexarray.h"
VertexArrayComponent VertexArray::Construct(std::vector<float> vertices) {   
    VertexArrayComponent v{};
    glGenVertexArrays(1, &v.VAO);
    glGenBuffers(1, &v.VBO);

    glBindVertexArray(v.VAO); 

    glBindBuffer(GL_ARRAY_BUFFER, v.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                vertices.data(), GL_STATIC_DRAW);
    
    //Vertex Data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    //Texture Data
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    v.verticesSize = vertices.size();
    return v;
}
void VertexArray::Deconstruct(VertexArrayComponent v) {
    glDeleteVertexArrays(1, &v.VAO);
    glDeleteBuffers(1, &v.VBO);
}

void VertexArray::Draw(VertexArrayComponent v){
    glBindVertexArray(v.VAO); 
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
