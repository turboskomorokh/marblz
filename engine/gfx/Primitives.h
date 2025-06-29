//
// Created by paul on 29.06.25.
//

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <sys/types.h>

#include "Geometry.h"

#endif //PRIMITIVES_H

namespace marblz::gfx {
    // FRONT (+Z)
    static inline constexpr geometry::Vertex CUBE_FACE_FRONT[] = {
      {{0, 0, 1}, {0.0f, 0.0f}, {0, 0, 1}},
      {{1, 0, 1}, {1.0f, 0.0f}, {0, 0, 1}},
      {{1, 1, 1}, {1.0f, 1.0f}, {0, 0, 1}},
      {{0, 1, 1}, {0.0f, 1.0f}, {0, 0, 1}}
    };

    // BACK (-Z)
    static inline constexpr geometry::Vertex CUBE_FACE_BACK[] = {
      {{1, 0, 0}, {0.0f, 0.0f}, {0, 0, -1}},
      {{0, 0, 0}, {1.0f, 0.0f}, {0, 0, -1}},
      {{0, 1, 0}, {1.0f, 1.0f}, {0, 0, -1}},
      {{1, 1, 0}, {0.0f, 1.0f}, {0, 0, -1}}
    };

    // LEFT (-X)
    static inline constexpr geometry::Vertex CUBE_FACE_LEFT[] = {
      {{0, 0, 0}, {0.0f, 0.0f}, {-1, 0, 0}},
      {{0, 0, 1}, {1.0f, 0.0f}, {-1, 0, 0}},
      {{0, 1, 1}, {1.0f, 1.0f}, {-1, 0, 0}},
      {{0, 1, 0}, {0.0f, 1.0f}, {-1, 0, 0}}
    };

    // RIGHT (+X)
    static inline constexpr geometry::Vertex CUBE_FACE_RIGHT[] = {
      {{1, 0, 1}, {0.0f, 0.0f}, {1, 0, 0}},
      {{1, 0, 0}, {1.0f, 0.0f}, {1, 0, 0}},
      {{1, 1, 0}, {1.0f, 1.0f}, {1, 0, 0}},
      {{1, 1, 1}, {0.0f, 1.0f}, {1, 0, 0}}
    };

    // TOP (+Y)
    static inline constexpr geometry::Vertex CUBE_FACE_TOP[] = {
      {{0, 1, 1}, {0.0f, 0.0f}, {0, 1, 0}},
      {{1, 1, 1}, {1.0f, 0.0f}, {0, 1, 0}},
      {{1, 1, 0}, {1.0f, 1.0f}, {0, 1, 0}},
      {{0, 1, 0}, {0.0f, 1.0f}, {0, 1, 0}}
    };

    // BOTTOM (-Y)
    static inline constexpr geometry::Vertex CUBE_FACE_BOTTOM[] = {
      {{0, 0, 0}, {0.0f, 0.0f}, {0, -1, 0}},
      {{1, 0, 0}, {1.0f, 0.0f}, {0, -1, 0}},
      {{1, 0, 1}, {1.0f, 1.0f}, {0, -1, 0}},
      {{0, 0, 1}, {0.0f, 1.0f}, {0, -1, 0}}
    };

    static inline constexpr unsigned int CUBE_FACE_INDICES[] = {
      0, 1, 2,
      2, 3, 0
  };

}