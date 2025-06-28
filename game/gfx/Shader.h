//
// Created by paul on 28.06.25.
//

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

static const std::string defaultVertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec2 v_texCoord;

uniform mat4 u_mvp;

out vec4 a_color;
out vec2 a_texCoord;

void main() {
  a_color = vec4(1,1,1,1);
  a_texCoord = v_texCoord;
  gl_Position = u_mvp * vec4(v_position, 1.0);
}
)";

static const std::string defaultFragmentShaderSource = R"(
#version 330 core
in vec2 a_texCoord;
out vec4 frag_color;

uniform sampler2D u_texture0;

void main() {
    frag_color = texture(u_texture0, a_texCoord);
}
)";

class Shader {
public:
  Shader();
  Shader(const std::string &vertexSource, const std::string &fragmentSource);
  ~Shader();

  int compile();

  void bind() const;
  void unbind() const;

  void setMat4(const char* name, glm::mat4 mvp);

private:
  std::string vertexSource, fragmentSource;
  unsigned int id;
};


#endif //SHADER_H
