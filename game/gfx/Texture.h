//
// Created by paul on 28.06.25.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <GL/glew.h>

#include <png.h>
#include <GL/gl.h>
#include <stdexcept>
#include <vector>
#include <fstream>

namespace marblz::gfx {
  class Texture {
  public:
    unsigned int id;

    explicit Texture(unsigned int id);
    void bind() const;
    ~Texture();
    void unbind() const;
  };

  class TextureManager {
  public:
    static Texture LoadTexturePNG(const std::string &path);
  };
}

#endif //TEXTURE_H
