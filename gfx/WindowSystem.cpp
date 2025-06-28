//
// Created by turbo on 28.06.25.
//

#include <stdexcept>
#include <spdlog/spdlog.h>
#include <format>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <chrono>

#include "WindowSystem.hpp"

void WindowSystem::glfwErrorHandler(int error_code, const char *description) {
  std::string errmsg = std::format("GLFW ERROR! CODE {}:\n{}", error_code, description);
  spdlog::critical(errmsg);
  throw std::runtime_error(errmsg);
}

void WindowSystem::glfwResizeHandler(GLFWwindow *window, int width, int height) {

}

void WindowSystem::init() {
  glfwSetErrorCallback(glfwErrorHandler);
  if (!glfwInit()) {
    throw std::runtime_error("GLFW init failed");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  mainWindow = glfwCreateWindow(480, 360, "Window", nullptr, nullptr);
  if (!mainWindow) {
    throw std::runtime_error("Failed to create window");
  }

  contextThread = std::jthread([=](std::stop_token token) {
    glfwMakeContextCurrent(mainWindow);

    renderer->init();

    while (!glfwWindowShouldClose(mainWindow) && !token.stop_requested()) {
      spdlog::info("Log from contextThread");
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(0.1, 0.3, 0.3, 1.0);
      glfwSwapBuffers(mainWindow);
      glfwPollEvents();
      std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    renderer->finalize();

    glfwMakeContextCurrent(nullptr);
  });
}

GLFWwindow *WindowSystem::getWindow() { return mainWindow; }

void WindowSystem::resize(unsigned int width, unsigned int height) {
  glfwSetWindowSize(mainWindow, width, height);
}

void WindowSystem::finalize() {
  contextThread.request_stop();
  if (contextThread.joinable()) {
    contextThread.join();
  }
  if (mainWindow) {
    glfwDestroyWindow(mainWindow);
    mainWindow = nullptr;
  }
  glfwTerminate();
}

void WindowSystem::attachRenderer(enum RendererType rendererType) {
  WindowSystem::rendererType = rendererType;
  switch (rendererType) {
    default:
      detachRenderer();
      break;
    case RendererType::OpenGL:
      renderer = new GLRenderer();
      break;
    case RendererType::OpenGL_ES:
      renderer = new GLESRenderer();
      break;
  }
}

void WindowSystem::detachRenderer() {
  if (rendererType != RendererType::NONE)
    delete renderer;
  renderer = nullptr;
}

void WindowSystem::title(const char *title) {
  if (mainWindow) {
    glfwSetWindowTitle(mainWindow, title);
  }
}

void WindowSystem::waitForClose() {
  while (!glfwWindowShouldClose(WindowSystem::getWindow())) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}
