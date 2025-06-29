//
// Created by paul on 28.06.25.
//

#include "Shader.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <spdlog/spdlog.h>

namespace marblz::gfx {
  Shader::Shader()
    : vertexSource(DefaultVertexShaderSource),
      fragmentSource(DefaultFragmentShaderSource), id(0) {
    compile();
  }

  Shader::Shader(const std::string &vertexSource,
                 const std::string &fragmentSource)
    : vertexSource(vertexSource),
      fragmentSource(fragmentSource), id(0)
  {
    compile();
  }

  Shader::~Shader() {
    glDeleteProgram(id);
  }

  int Shader::compile() {
    unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
    unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
    int result;
    char infoLog[512];

    const char *vertSource = vertexSource.c_str();
    const char *fragSource = fragmentSource.c_str();

    glShaderSource(vert, 1, &vertSource, NULL);
    glShaderSource(frag, 1, &fragSource, NULL);

    glCompileShader(vert);

    glGetShaderiv(vert, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
      glGetShaderInfoLog(vert, 512, NULL, infoLog);
      spdlog::error("[SHADER] Unable to compile vertex shader:\n{}", infoLog);
      glDeleteShader(vert);
      glDeleteShader(frag);
      return false;
    }

    glCompileShader(frag);

    glGetShaderiv(frag, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
      glGetShaderInfoLog(frag, 512, NULL, infoLog);
      spdlog::error("[SHADER] Unable to compile fragment shader:\n{}", infoLog);
      glDeleteShader(vert);
      glDeleteShader(frag);
      return false;
    }

    id = glCreateProgram();

    glAttachShader(id, vert);
    glAttachShader(id, frag);

    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
      glGetProgramInfoLog(id, 512, NULL, infoLog);
      spdlog::error("[SHADER] Unable to link shader program:\n{}", infoLog);
      glDeleteShader(vert);
      glDeleteShader(frag);
      glDeleteProgram(id);
      id = 0;
      return false;
    }
    glDeleteShader(vert);
    glDeleteShader(frag);

    return true;
  }

  void Shader::bind() const {
    glUseProgram(id);
  }

  void Shader::unbind() const {
    glUseProgram(0);
  }

  void Shader::setMat4(const char* name, glm::mat4 mvp) {
    const int location = glGetUniformLocation(id, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mvp));
  }
}