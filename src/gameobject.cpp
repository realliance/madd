#include "gameobject.h"

GameObject::GameObject():rendered(false){

}

GameObject::~GameObject(){

}

bool GameObject::ReloadShader() {
    if(rendered){
        ShaderProgram* _shader;
        try {
        _shader = new ShaderProgram(vsPath, fsPath);
        } catch (int e) {
            return false;
        }
        if (shader) 
            delete shader;
        shader = _shader;
            return true;
    }else
        return false;
}

bool GameObject::RenderInit(std::vector<float> _vertices, std::vector<unsigned int> _indices, std::string vertexShader, std::string fragmentShader){
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
    VAO = new VertexArray(vertices, indices);
    rendered=true;

    shaderTimeLocation = glGetUniformLocation(shader->GetID(), "time");
    return true;
}

#include <glad/glad.h>
#include <GLFW/glfw3.h>
bool GameObject::Render(){
    if(rendered){
        glUseProgram(shader->GetID());
        glUniform1f(shaderTimeLocation, glfwGetTime());
        VAO->Bind();

        glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
        VertexArray::UnBind();
        return true;
    }else{
        return false;
    }
}