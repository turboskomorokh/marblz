//
// Created by paul on 28.06.25.
//

#include "Geometry.h"

#include <GL/glew.h>
#include <spdlog/spdlog.h>

namespace marblz::gfx::geometry {
  Mesh::Mesh() : vertices({}), indices({}) { build(); }
  Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) : vertices(vertices),
    indices(indices) {
    build();
  }

  void Mesh::update(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) {
    this->vertices = vertices;
    this->indices = indices;

    build();
  }

  void Mesh::build() {
    this->clean();
    if (vertices.empty() || indices.empty()) {
      spdlog::warn("Issued Mesh::build() with empty vertices or indices array. Skipping.");
      return;
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, uv));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
  }

  void Mesh::draw() const {
    if (VAO == 0) {
      spdlog::warn("Issued Mesh::draw() with NULL VAO. Skipping.");
      return;
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  void Mesh::clean() {
    if (VAO) {
      glDeleteVertexArrays(1, &VAO);
      VAO = 0;
    }
    if (VBO) {
      glDeleteBuffers(1, &VBO);
      VBO = 0;
    }
    if (EBO) {
      glDeleteBuffers(1, &EBO);
      EBO = 0;
    }
  }

  Mesh::~Mesh() {
    this->clean();
  }
}
