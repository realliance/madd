#include "shaderprogram.h"

ShaderProgram::ShaderProgram(Shader* vs, Shader* fs){

  id = glCreateProgram();
  glAttachShader(id, vs->Link(id));
  glAttachShader(id, fs->Link(id));
  glLinkProgram(id);

  int success;
  char infoLog[512];
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
    throw LINKING_FAILED; 
  }
}

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(id);
}