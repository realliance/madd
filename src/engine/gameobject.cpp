#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gameobject.h"
#include "madd.h"

GameObject::GameObject(Madd* context):rendered(false),context(context){

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
    

    transformLoc = glGetUniformLocation(shader->GetID(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    return true;
}

bool GameObject::Render(){
    if(rendered){
        glUseProgram(shader->GetID());
        VAO->Bind();

        glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
        VertexArray::UnBind();
        return true;
    }else{
        return false;
    }
}

bool GameObject::Update(){
    glUniform1f(shaderTimeLocation, context->time);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    trans = glm::rotate(trans, ((int)context->time%360)/100.f, glm::vec3(1.0, 0.0, 1.0));
    return true;
}