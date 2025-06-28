#include <spdlog/spdlog.h>
#include <chrono>

#include "gfx/WindowSystem.hpp"

int main() {
  spdlog::info("Hello!");
  WindowSystem::init();
  WindowSystem::attachRenderer(RendererType::OpenGL);

  WindowSystem::waitForClose();

  WindowSystem::finalize();
  return 0;
}