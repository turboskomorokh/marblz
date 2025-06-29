//
// Created by paul on 28.06.25.
//

#include <spdlog/spdlog.h>
#include <GL/glew.h>

#include "Window.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace marblz {
  void Window::glfwErrorCallback(int error_code, const char * description) {
    throw std::runtime_error(std::format("GLFW Error {}:\n{}", error_code, description));
  }

  void Window::glfwResizeCallback(GLFWwindow * window, int width, int height) {
    glViewport(0, 0, width, height);
    projection =  glm::perspective(glm::radians(45.0f),
                                          static_cast<float>(width) / static_cast<float>(height),
                                          0.1f, 100.0f);
  }

  void Window::initialize(int width, int height, const char* title) {
    glfwSetErrorCallback(glfwErrorCallback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(width, height, "", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
      throw std::runtime_error("Failed to initialize GLEW");
    }

    glViewport(0, 0, width, height);
    glfwSetWindowSizeCallback(window, glfwResizeCallback);
    projection = glm::perspective(glm::radians(45.0f),
                                          static_cast<float>(width) / static_cast<float>(height),
                                          0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void Window::initialize() {
    initialize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "");
  }

  void Window::terminate() {
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  glm::mat4 Window::getProjection() {
    return projection;
  }

  void Window::setShouldClose(bool value) {
    glfwSetWindowShouldClose(window, value);
  }

  bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
  }

  void Window::swapBuffers() {
    glfwSwapBuffers(window);
  }
}