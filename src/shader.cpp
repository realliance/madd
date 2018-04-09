#include "shader.h"

Shader::Shader(std::string shaderSourceCode, unsigned int shaderType)
    : source(shaderSourceCode.c_str()), shaderType(shaderType) {
  Init();
}

Shader::Shader(std::string shaderFileName) {
  std::ifstream file;
  file.open("shaders\\" + shaderFileName);
  std::string shaderSourceCode((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());
  Init();
}

void Shader::Init() {
  id = glCreateShader(shaderType);
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);

  char infoLog[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(id, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

Shader::~Shader() {
  glDeleteShader(id);
  // delete[] source;
}