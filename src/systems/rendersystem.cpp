#include "rendersystem.h"
#include "madd.h"
#include "camerasystem.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shadersystem.h"
#include "meshsystem.h"
#include "texturesystem.h"

void RenderSystem::FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    // CameraSystem::UpdateProjection(*Madd::GetInstance().GetMainCamera());
}

void RenderSystem::ErrorCallback(int, const char* err_str) {
    std::cout << "GLFW Error: " << err_str << std::endl;
}

void RenderSystem::Init() {
    const char *title = "test";
    int width = 800;
    int height = 600;

    glfwSetErrorCallback(ErrorCallback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
}

void RenderSystem::Deinit(){
    glfwSetFramebufferSizeCallback(window, nullptr);
    glfwDestroyWindow(window);
    glfwSetErrorCallback(nullptr);
    // glfwTerminate();
}

bool RenderSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  objects.push_back(dynamic_cast<RenderedComponent*>(component));
  return true;
}



bool RenderSystem::Unregister(Component* component){
  for(auto i = begin(objects); i != end(objects); i++){
    if((*i)->cID == component->cID){
      objects.erase(i);
      return true;
    }
  }
  return false;
}

void RenderSystem::Update(){
  Start();
  CameraSystem* csys= dynamic_cast<CameraSystem*>(Madd::GetInstance().GetSystem("CameraSystem"));
  for(auto const c : csys->GetCameras()){
    for (RenderedComponent *r : objects) {
      updateComponent(*r,*c);
    }
  }
  Finish();
}


void RenderSystem::updateComponent(RenderedComponent& r, CameraComponent& c){
  ShaderSystem::Enable(*r.shader);
  ShaderSystem::SetFloat4fUniform(ShaderSystem::GetUniformLocation(*r.shader, "shade"), &r.shade);
  ShaderSystem::SetMartix4fUniform(ShaderSystem::GetUniformLocation(*r.shader, "model"), &r.model);
  ShaderSystem::SetMartix4fUniform(ShaderSystem::GetUniformLocation(*r.shader, "view"), &c.view);
  ShaderSystem::SetMartix4fUniform(ShaderSystem::GetUniformLocation(*r.shader, "projection"), &c.projection);
  ShaderSystem::SetFloatUniform(ShaderSystem::GetUniformLocation(*r.shader, "time"), Madd::GetInstance().GetTime());
  if(r.texture){
    ShaderSystem::SetIntUniform(ShaderSystem::GetUniformLocation(*r.shader, "textureEnabled"),1);
    TextureSystem::Enable(r.texture);
  }else{
    ShaderSystem::SetIntUniform(ShaderSystem::GetUniformLocation(*r.shader, "textureEnabled"),0);
  }

  MeshSystem::Draw(*r.mesh);
}

RenderSystem& RenderSystem::GetInstance() {

    static RenderSystem r;
    return r;
}


void RenderSystem::Start(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::Finish(){
    glfwSwapBuffers(window);
}

int RenderSystem::GetHeight(){
    int height;
    glfwGetWindowSize(window, NULL, &height);
    return height;
}

int RenderSystem::GetWidth(){
    int width;
    glfwGetWindowSize(window, &width, NULL);
    return width;
}
