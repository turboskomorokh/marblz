//
// Created by paul on 28.06.25.
//

#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <vector>
#include <glm/glm.hpp>

namespace marblz::gfx::geometry {
  struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
  };

  class Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO = 0, VBO = 0, EBO = 0;

  public:
    Mesh();
    Mesh(const std::vector<Vertex> &vertices,
         const std::vector<unsigned int> &indices);
    ~Mesh();
    void update(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);


    void draw() const;

  private:
    void build();
    void clean();
  };
}

#endif //GEOMETRY_H
