#include <spdlog/spdlog.h>
#include <chrono>
#include <GL/glew.h>
#include <glm/vec2.hpp>

#include "game/Camera.h"
#include "game/Events.h"
#include "game/Window.h"
#include "game/gfx/Shader.h"
#include "game/gfx/Texture.h"

struct trivert {
  glm::vec3 pos;
  glm::vec2 uv;
};

int main() {
  spdlog::info("Hello!");
  Window::initialize();
  Events::initialize();

  Shader shader;
  trivert triverts[] = {
    {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}}, // левый нижний
    {{0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}}, // правый нижний
    {{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f}}, // правый верхний
    {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}} // левый верхний
  };

  GLuint indices[] = {0, 1, 2, 2, 3, 0};

  unsigned int VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  // VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triverts), triverts, GL_STATIC_DRAW);

  // Настройка атрибутов
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(trivert), static_cast<void *>(nullptr));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(trivert), reinterpret_cast<void *>(offsetof(trivert, uv)));
  glEnableVertexAttribArray(1);
  // EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindVertexArray(0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);

  Camera camera(glm::vec3(0.0f, 0.0f, 3.0f),
                glm::vec3(0.0f, 1.0f, 0.0f),
                -90.0f, 0.0f);

  Events::attachCamera(&camera);

  Texture texture = TextureManager::LoadTexturePNG("./texture.png");
  while (!Window::shouldClose()) {
    glm::mat4 mvp = Window::getProjection() * camera.getViewMatrix() * glm::mat4(1.0f);
    Events::poll();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.3f, 0.3f, 1.0f);

    shader.bind();
    shader.setMat4("u_mvp", mvp);
    texture.bind();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    texture.unbind();

    shader.unbind();

    Window::swapBuffers();
  }

  Window::terminate();

  return 0;
}
