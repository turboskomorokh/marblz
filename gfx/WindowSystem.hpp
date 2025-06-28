//
// Created by turbo on 28.06.25.
//

#ifndef MARBL_WINDOWSYSTEM_HPP
#define MARBL_WINDOWSYSTEM_HPP

#include <GLFW/glfw3.h>

#include "Renderer.hpp"

class WindowSystem
{
public:
  static void init();
  static void finalize();

  static void resize(unsigned int width, unsigned int height);
  static void title(const char *title);

  static GLFWwindow *getWindow();
  static void attachRenderer(enum RendererType);
  static void detachRenderer();

  static void waitForClose();

private:
  static inline GLFWwindow *mainWindow = nullptr;
  static inline std::jthread contextThread;
  static inline IGLRenderer *renderer;
  static inline enum RendererType rendererType = RendererType::NONE;

  static void glfwErrorHandler(int, const char*);
  static void glfwResizeHandler(GLFWwindow*, int, int);
};


#endif //MARBL_WINDOWSYSTEM_HPP
