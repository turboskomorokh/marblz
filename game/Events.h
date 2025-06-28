//
// Created by paul on 28.06.25.
//

#ifndef EVENTS_H
#define EVENTS_H
#include <memory>
#include <GLFW/glfw3.h>
#include <sys/types.h>

#include "Camera.h"


class Events {
public:
  static inline bool *keys = nullptr;
  static inline uint *frames = nullptr;
  static inline uint current = 0;

  static inline float deltaX = 0.0f, deltaY = 0.0f;
  static inline float mouseX = 0.0f, mouseY = 0.0f;
  static inline bool cursorLocked = false, cursorStarted = false;

  static void initialize();
  static void finalize();

  static bool isPressed(int keycode);
  static bool isClicked(int keycode);

  static bool isJustPressed(int keycode);
  static bool isJustClicked(int keycode);

  static void poll();

  static void attachCamera(Camera* cam);
  static void detachCamera();

  static void updateCamera();

private:
  static inline Camera* camera = nullptr;
};



#endif //EVENTS_H
