//
// Created by paul on 29.06.25.
//
#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>

#include "Geometry.h"

#endif //PRIMITIVES_H

namespace marblz::gfx::geometry::primitives {
  static inline const std::vector<Vertex> PLANE = {
    {{0, 0, 0}, {0.0f, 0.0f}, {0, 0, 1}}, // bottom-left
    {{1, 0, 0}, {1.0f, 0.0f}, {0, 0, 1}}, // bottom-right
    {{1, 1, 0}, {1.0f, 1.0f}, {0, 0, 1}}, // top-right
    {{0, 1, 0}, {0.0f, 1.0f}, {0, 0, 1}} // top-left
  };

  static inline const uint32_t PLANE_INDICES[] = {
    0, 1, 2,
    2, 1, 3
  };

  enum class CubeFace {
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
  };

  // FRONT (+Z)
  static inline const std::vector<Vertex> CUBE_FACES = {
    {{0, 0, 1}, {0.0f, 0.0f}, {0, 0, 1}, (int) CubeFace::FRONT},
    {{1, 0, 1}, {1.0f, 0.0f}, {0, 0, 1}, (int) CubeFace::FRONT},
    {{1, 1, 1}, {1.0f, 1.0f}, {0, 0, 1}, (int) CubeFace::FRONT},
    {{0, 1, 1}, {0.0f, 1.0f}, {0, 0, 1}, (int) CubeFace::FRONT},

    {{1, 0, 0}, {0.0f, 0.0f}, {0, 0, -1}, (int) CubeFace::BACK},
    {{0, 0, 0}, {1.0f, 0.0f}, {0, 0, -1}, (int) CubeFace::BACK},
    {{0, 1, 0}, {1.0f, 1.0f}, {0, 0, -1}, (int) CubeFace::BACK},
    {{1, 1, 0}, {0.0f, 1.0f}, {0, 0, -1}, (int) CubeFace::BACK},

    {{0, 0, 0}, {0.0f, 0.0f}, {-1, 0, 0}, (int) CubeFace::LEFT},
    {{0, 0, 1}, {1.0f, 0.0f}, {-1, 0, 0}, (int) CubeFace::LEFT},
    {{0, 1, 1}, {1.0f, 1.0f}, {-1, 0, 0}, (int) CubeFace::LEFT},
    {{0, 1, 0}, {0.0f, 1.0f}, {-1, 0, 0}, (int) CubeFace::LEFT},

    {{1, 0, 1}, {0.0f, 0.0f}, {1, 0, 0}, (int) CubeFace::RIGHT},
    {{1, 0, 0}, {1.0f, 0.0f}, {1, 0, 0}, (int) CubeFace::RIGHT},
    {{1, 1, 0}, {1.0f, 1.0f}, {1, 0, 0}, (int) CubeFace::RIGHT},
    {{1, 1, 1}, {0.0f, 1.0f}, {1, 0, 0}, (int) CubeFace::RIGHT},

    {{0, 1, 1}, {0.0f, 0.0f}, {0, 1, 0}, (int) CubeFace::TOP},
    {{1, 1, 1}, {1.0f, 0.0f}, {0, 1, 0}, (int) CubeFace::TOP},
    {{1, 1, 0}, {1.0f, 1.0f}, {0, 1, 0}, (int) CubeFace::TOP},
    {{0, 1, 0}, {0.0f, 1.0f}, {0, 1, 0}, (int) CubeFace::TOP},

    {{0, 0, 0}, {0.0f, 0.0f}, {0, -1, 0}, (int) CubeFace::BOTTOM},
    {{1, 0, 0}, {1.0f, 0.0f}, {0, -1, 0}, (int) CubeFace::BOTTOM},
    {{1, 0, 1}, {1.0f, 1.0f}, {0, -1, 0}, (int) CubeFace::BOTTOM},
    {{0, 0, 1}, {0.0f, 1.0f}, {0, -1, 0}, (int) CubeFace::BOTTOM},
  };

  static inline const std::vector<unsigned int> CUBE_FACE_INDICES = {
    // FRONT
    0, 1, 2,
    2, 3, 0,

    // BACK
    4, 5, 6,
    6, 7, 4,

    // LEFT
    8, 9, 10,
    10, 11, 8,

    // RIGHT
    12, 13, 14,
    14, 15, 12,

    // TOP
    16, 17, 18,
    18, 19, 16,

    // BOTTOM
    20, 21, 22,
    22, 23, 20
  };
}
