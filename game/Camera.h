//
// Created by paul on 28.06.25.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
  glm::vec3 position;
  glm::vec3 front{};
  glm::vec3 up{} ;
  glm::vec3 right{};
  const glm::vec3 worldUp{0.0f, 1.0f, 0.0f};

  float yaw;
  float pitch;

  Camera(glm::vec3 pos, glm::vec3 upDir, float yawDeg, float pitchDeg);
  [[nodiscard]] glm::mat4 getViewMatrix() const;

  void moveX(float delta);
  void moveY(float delta);
  void moveZ(float delta);
  void updateVectors();
};


#endif //CAMERA_H
