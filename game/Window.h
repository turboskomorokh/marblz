//
// Created by paul on 28.06.25.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define DEFAULT_WINDOW_WIDTH 600
#define DEFAULT_WINDOW_HEIGHT 600

namespace marblz {
  class Window {
  public:
    static void initialize();
    static void initialize(int width, int height, const char *title);
    static void terminate();

    static glm::mat4 getProjection();

    static void setShouldClose(bool value);
    static bool shouldClose();

    static void swapBuffers();
    static inline GLFWwindow *window = nullptr;

  private:
    static inline glm::mat4 projection;
    static void glfwErrorCallback(int error_code, const char *description);
    static void glfwResizeCallback(GLFWwindow *window, int width, int height);
  };
}

#endif //WINDOW_H
