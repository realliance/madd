#include "renderedobject.h"
#include "madd.h"

RenderedObject::RenderedObject(GameObject* parent):parent(parent){
}

RenderedObject::~RenderedObject(){
    delete VAO;
    delete shader;
    delete textureObj;
}

bool RenderedObject::RenderInit(std::vector<float> vertices,
                                std::vector<unsigned int> indices,
                                std::string vertexShader,
                                std::string fragmentShader,
                                std::string texture){
    vsPath = vertexShader;
    fsPath = fragmentShader;
    try {
        shader = new ShaderProgram(vsPath, fsPath);
    } catch (int e) {
        return false;
    }
    VAO = new VertexArray(vertices, indices);
    textureObj = new Texture(texture);
    shader->Enable();
    shader->AddInt("texture1",0);
    
    shaderTimeLocation = shader->GetUniformLocation("time");
    transformLoc = shader->GetUniformLocation("transform");
    shader->SetMartix4fUniform(transformLoc, &trans);
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
    shaderTimeLocation = shader->GetUniformLocation("time");
    transformLoc = shader->GetUniformLocation("transform");
    ShaderProgram::SetMartix4fUniform(transformLoc, &trans);
    return true;
}

bool RenderedObject::Render(){
    ShaderProgram::SetFloatUniform(shaderTimeLocation, parent->GetContext()->GetTime());
    shader->Enable();
    Texture::SetActiveTexture(0);
    textureObj->Enable();

    VAO->Draw();
    return true;
}

glm::mat4 RenderedObject::GetTransformation(){
    return trans;
}
void RenderedObject::SetTransformation(glm::mat4 newMatrix){
    trans = newMatrix;
    ShaderProgram::SetMartix4fUniform(transformLoc, &trans);
}