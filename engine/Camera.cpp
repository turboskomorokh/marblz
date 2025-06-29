//
// Created by paul on 28.06.25.
//

#include "Camera.h"

namespace marblz {
  Camera::Camera(glm::vec3 pos, glm::vec3 upDir, float yawDeg, float pitchDeg): position(pos), worldUp(upDir), yaw(yawDeg), pitch(pitchDeg) {
    updateVectors();
  }

  glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
  }

  void Camera::moveX(float delta) {
    position += right * delta;
  }

  void Camera::moveY(float delta) {
    position.y += delta;
  }

  void Camera::moveZ(float delta) {
    position += front * delta;
  }

  void Camera::updateVectors() {
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);

    // Правая и верхняя
    right = glm::normalize(glm::cross(front, worldUp));
    up    = glm::normalize(glm::cross(right, front));
  }
}