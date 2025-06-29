#include <spdlog/spdlog.h>
#include <chrono>
#include <GL/glew.h>
#include <glm/vec2.hpp>

#include "game/Camera.h"
#include "game/Events.h"
#include "game/Window.h"
#include "game/gfx/Geometry.h"
#include "game/gfx/Shader.h"
#include "game/gfx/Texture.h"

using namespace marblz;

int main() {
  spdlog::info("Hello!");
  Window::initialize();
  Events::initialize();

  gfx::Shader shader;

  std::vector<gfx::geometry::Vertex> vertices = {
    {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}}, // левый нижний
    {{0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}}, // правый нижний
    {{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f}}, // правый верхний
    {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}} // левый верхний
  };

  std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0};

  gfx::geometry::Mesh mesh(vertices, indices);

  Camera camera(glm::vec3(0.0f, 0.0f, 3.0f),
                glm::vec3(0.0f, 1.0f, 0.0f),
                -90.0f, 0.0f);

  Events::attachCamera(&camera);

  gfx::Texture texture = gfx::TextureManager::LoadTexturePNG("./res/texture.png");
  while (!Window::shouldClose()) {
    glm::mat4 mvp = Window::getProjection() * camera.getViewMatrix() * glm::mat4(1.0f);
    Events::poll();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.3f, 0.3f, 1.0f);

    shader.bind();
    shader.setMat4("u_mvp", mvp);
    texture.bind();
    mesh.draw();
    texture.unbind();
    shader.unbind();

    Window::swapBuffers();
  }

  Events::finalize();
  Window::terminate();

  return 0;
}
