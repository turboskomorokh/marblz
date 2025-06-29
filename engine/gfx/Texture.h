//
// Created by paul on 28.06.25.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "engine/assets/Image.hpp"

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
    static Texture Load(const assets::Image& img);
  };
}

#endif //TEXTURE_H
