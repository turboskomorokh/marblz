#include <spdlog/spdlog.h>
#include <chrono>
#include <GL/glew.h>
#include <glm/vec2.hpp>

#include "engine/Camera.h"
#include "engine/Events.h"
#include "engine/Window.h"
#include "engine/assets/ImageManager.hpp"
#include "engine/gfx/Geometry.h"
#include "engine/gfx/Primitives.h"
#include "engine/gfx/Shader.h"
#include "engine/gfx/Texture.h"

using namespace marblz;

glm::vec2 offsetUV(glm::vec2 uv, float tileX, float tileY) {
  constexpr float tilesX = 3.0f;
  constexpr float tilesY = 2.0f;
  return {
      (uv.x + tileX) / tilesX,
      (uv.y + tileY) / tilesY
  };
}

int main() {
  spdlog::info("Hello!");
  Window::initialize();
  Events::initialize();

  gfx::Shader shader;

  std::vector<gfx::geometry::Vertex> cubeVertices;
  std::vector<unsigned int> cubeIndices = gfx::geometry::primitives::CUBE_FACE_INDICES;

  for (auto vertex : gfx::geometry::primitives::CUBE_FACES) {
    switch (static_cast<gfx::geometry::primitives::CubeFace>(vertex.flag)) {
      case gfx::geometry::primitives::CubeFace::FRONT:
        vertex.uv = offsetUV(vertex.uv, 0, 0);
        break;
      case gfx::geometry::primitives::CubeFace::BACK:
        vertex.uv = offsetUV(vertex.uv, 1, 0);
        break;
      case gfx::geometry::primitives::CubeFace::LEFT:
        vertex.uv = offsetUV(vertex.uv, 2, 0);
        break;
      case gfx::geometry::primitives::CubeFace::RIGHT:
        vertex.uv = offsetUV(vertex.uv, 0, 1);
        break;
      case gfx::geometry::primitives::CubeFace::TOP:
        vertex.uv = offsetUV(vertex.uv, 1, 1);
        break;
      case gfx::geometry::primitives::CubeFace::BOTTOM:
        vertex.uv = offsetUV(vertex.uv, 2, 1);
        break;
    }
    cubeVertices.push_back(vertex);
  }

  gfx::geometry::Mesh mesh(cubeVertices, gfx::geometry::primitives::CUBE_FACE_INDICES);

  Camera camera(glm::vec3(0.0f, 0.0f, 3.0f),
                glm::vec3(0.0f, 1.0f, 0.0f),
                -90.0f, 0.0f);

  Events::attachCamera(&camera);

  gfx::Texture texture = gfx::TextureManager::Load(assets::ImageManager::loadPNG("./res/atlas.png"));
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
