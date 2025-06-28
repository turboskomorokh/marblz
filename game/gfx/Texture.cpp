//
// Created by paul on 28.06.25.
//

#include "Texture.h"

#include <cstring>

void flipImageVertically(unsigned char* data, int width, int height, int channels) {
  int rowSize = width * channels;
  std::vector<unsigned char> tempRow(rowSize);
  for (int y = 0; y < height / 2; ++y) {
    unsigned char* top = data + y * rowSize;
    unsigned char* bottom = data + (height - 1 - y) * rowSize;

    // Обмен строк местами
    memcpy(tempRow.data(), top, rowSize);
    memcpy(top, bottom, rowSize);
    memcpy(bottom, tempRow.data(), rowSize);
  }
}

Texture::Texture(unsigned int id) : id(id) {}

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

Texture TextureManager::LoadTexturePNG(const std::string &path) {
  FILE *fp = fopen(path.c_str(), "rb");
  if (!fp) {
    throw std::runtime_error("Failed to open file: " + path);
  }

  // Проверяем сигнатуру PNG
  png_byte header[8];
  fread(header, 1, 8, fp);
  if (png_sig_cmp(header, 0, 8)) {
    fclose(fp);
    throw std::runtime_error("Not a PNG file: " + path);
  }

  // Создаём структуры libpng
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (!png_ptr) {
    fclose(fp);
    throw std::runtime_error("png_create_read_struct failed");
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, nullptr, nullptr);
    fclose(fp);
    throw std::runtime_error("png_create_info_struct failed");
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    // Ошибка при чтении PNG
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    fclose(fp);
    throw std::runtime_error("Error during png read");
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);


  png_read_info(png_ptr, info_ptr);

  png_set_interlace_handling(png_ptr);

  png_uint_32 width = png_get_image_width(png_ptr, info_ptr);
  png_uint_32 height = png_get_image_height(png_ptr, info_ptr);
  png_byte color_type = png_get_color_type(png_ptr, info_ptr);
  png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  // Приводим данные к формату RGBA 8 бит
  if (bit_depth == 16)
    png_set_strip_16(png_ptr);

  if (color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png_ptr);

  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png_ptr);

  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png_ptr);

  if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY)
    png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);

  if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png_ptr);

  png_read_update_info(png_ptr, info_ptr);

  // Читаем строки изображения
  std::vector<png_bytep> row_pointers(height);
  std::vector<unsigned char> image_data(height * width * 4);
  for (size_t i = 0; i < height; ++i) {
    row_pointers[i] = &image_data[i * width * 4];
  }

  png_read_image(png_ptr, row_pointers.data());

  png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
  fclose(fp);

  GLuint texture_id;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data.data());

  return Texture(texture_id);
}