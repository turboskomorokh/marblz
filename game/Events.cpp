//
// Created by paul on 28.06.25.
//

#include <cstring>
#include <GLFW/glfw3.h>

#include "../utils/in_between.h"

#include "Events.h"
#include "Window.h"


#define MOUSE_BUTTON_OFFSET 1024

void cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
  if (Events::cursorLocked) {
    Events::deltaX += xpos - Events::mouseX;
    Events::deltaY += ypos - Events::mouseY;
  } else {
    Events::cursorStarted = true;
  }
  Events::mouseX = xpos;
  Events::mouseY = ypos;
}

void mouseCallback(GLFWwindow *window, int button, int action, int mods) {
  if (action == GLFW_PRESS) {
    Events::keys[MOUSE_BUTTON_OFFSET + button] = true;
    Events::frames[MOUSE_BUTTON_OFFSET + button] = Events::current;
  }
  if (action == GLFW_RELEASE) {
    Events::keys[MOUSE_BUTTON_OFFSET + button] = false;
    Events::frames[MOUSE_BUTTON_OFFSET + button] = Events::current;
  }
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
  if (action == GLFW_PRESS) {
    Events::keys[key] = true;
    Events::frames[key] = Events::current;
  } else if (action == GLFW_RELEASE) {
    Events::keys[key] = false;
    Events::frames[key] = Events::current;
  }
}

void Events::initialize() {
  GLFWwindow *window = Window::window;
  keys = new bool[1032];
  frames = new uint[1032];
  current = 0;

  memset(keys, 0, 1032);
  memset(frames, 0, 1032);

  glfwSetMouseButtonCallback(window, mouseCallback);
  glfwSetCursorPosCallback(window, cursorPosCallback);
  glfwSetKeyCallback(window, keyCallback);
}

void Events::finalize() {
  delete[] keys;
  delete[] frames;
}

bool Events::isPressed(int keycode) {
  if (!utils::in_between(keycode, 0, MOUSE_BUTTON_OFFSET - 1))
    return false;
  if (!keys || !frames) return false;
  return keys[keycode] && frames[keycode] == current;
}

bool Events::isJustPressed(int keycode) {
  if (!utils::in_between(keycode, 0, MOUSE_BUTTON_OFFSET - 1))
    return false;
  if (!keys) return false;
  return keys[keycode];
}

bool Events::isJustClicked(int keycode) {
  int index = MOUSE_BUTTON_OFFSET + keycode;
  if (!utils::in_between(index,MOUSE_BUTTON_OFFSET, 1031))
    return false;
  if (!keys) return false;
  return keys[index];
}

bool Events::isClicked(int keycode) {
  int index = MOUSE_BUTTON_OFFSET + keycode;
  if (!utils::in_between(index, MOUSE_BUTTON_OFFSET, 1031))
    return false;
  if (!keys || !frames) return false;
  return keys[index] && frames[index] == current;
}

void Events::poll() {
  current++;
  deltaX = 0.0f;
  deltaY = 0.0f;
  glfwPollEvents();

  if (isJustPressed(GLFW_KEY_ESCAPE))
    Window::setShouldClose(true);

  if (isPressed(GLFW_KEY_1)) {
    cursorLocked = !cursorLocked;
    if (cursorLocked) {
      glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      cursorStarted = false;
    } else {
      glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
  }

  if (camera) {
    updateCamera();
  }
}

void Events::attachCamera(Camera *cam) {
  camera = cam;
}

void Events::detachCamera() {
  camera = nullptr;
}

void Events::updateCamera() {
  if (!camera) return;
  if (isJustPressed(GLFW_KEY_W))
    camera->moveZ(0.05f);
  if (isJustPressed(GLFW_KEY_S))
    camera->moveZ(-0.05f);
  if (isJustPressed(GLFW_KEY_A))
    camera->moveX(-0.05f);
  if (isJustPressed(GLFW_KEY_D))
    camera->moveX(0.05f);

  if (isJustPressed(GLFW_KEY_SPACE))
    camera->moveY(0.05f);
  else if (isJustPressed(GLFW_KEY_LEFT_SHIFT))
    camera->moveY(-0.05f);


  if (cursorLocked && (deltaX != 0.0f || deltaY != 0.0f)) {
    float sensitivity = 0.1f;
    camera->yaw += deltaX * sensitivity;
    camera->pitch -= deltaY * sensitivity;

    if (camera->pitch > 89.0f) camera->pitch = 89.0f;
    if (camera->pitch < -89.0f) camera->pitch = -89.0f;

    camera->updateVectors();
  }
}
