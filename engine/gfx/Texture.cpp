//
// Created by paul on 28.06.25.
//

#include "engine/assets/Image.hpp"
#include "engine/gfx/Texture.h"

#include <GL/glew.h>

#include <cstring>

namespace marblz::gfx {
  void flipImageVertically(unsigned char* data, int width, int height, int channels) {
    int rowSize = width * channels;
    std::vector<unsigned char> tempRow(rowSize);
    for (int y = 0; y < height / 2; ++y) {
      unsigned char* top = data + y * rowSize;
      unsigned char* bottom = data + (height - 1 - y) * rowSize;
      memcpy(tempRow.data(), top, rowSize);
      memcpy(top, bottom, rowSize);
      memcpy(bottom, tempRow.data(), rowSize);
    }
  }

  Texture::Texture(const unsigned int id) : id(id) {}

  void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, id);
  }

  void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  Texture::~Texture() {
    if (id) {
      glDeleteTextures(1, &id);
    }
  }

  Texture TextureManager::Load(const assets::Image& img) {
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.imageData.data());

    return Texture(texture_id);
  }
}