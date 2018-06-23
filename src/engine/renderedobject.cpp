#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderedobject.h"
#include "madd.h"

RenderedObject::RenderedObject(GameObject* parent):parent(parent){
}

RenderedObject::~RenderedObject(){
    delete VAO;
    delete shader;
}

bool RenderedObject::RenderInit(std::vector<float> _vertices, std::vector<unsigned int> _indices, std::string vertexShader, std::string fragmentShader, bool rgbcolor=false){
    vsPath = vertexShader;
    fsPath = fragmentShader;
    try {
        shader = new ShaderProgram(vsPath, fsPath);
    } catch (int e) {
        return false;
    }
    vertices = _vertices;
    indices = _indices;
    indicesSize = indices.size();
    VAO = new VertexArray(vertices, indices, rgbcolor);
    
    shaderTimeLocation = glGetUniformLocation(shader->GetID(), "time");
    transformLoc = glGetUniformLocation(shader->GetID(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    return true;
}

bool RenderedObject::ReloadShader() {
    ShaderProgram* _shader;
    try {
        _shader = new ShaderProgram(vsPath, fsPath);
    } catch (int e) {
        return false;
    }
    if (shader) 
        delete shader;
    shader = _shader;
    
    //Update Locations for new shader
    shaderTimeLocation = glGetUniformLocation(shader->GetID(), "time");
    transformLoc = glGetUniformLocation(shader->GetID(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    return true;
}

bool RenderedObject::Render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniform1f(shaderTimeLocation, parent->GetContext()->GetTime());
    glUseProgram(shader->GetID());
    VAO->Bind();

    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
    VertexArray::UnBind();
    return true;
}

glm::mat4 RenderedObject::GetTransformation(){
    return trans;
}
void RenderedObject::SetTransformation(glm::mat4 newMatrix){
    trans = newMatrix;
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}