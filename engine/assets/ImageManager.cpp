//
// Created by turbo on 28.06.25.
//

#include "ImageManager.hpp"
#include "Image.hpp"

#include <stdexcept>
#include <cstring>
#include <format>

#include <png.h>


namespace marblz::assets {
  void flipImageVertically(Image &img) {
    int rowSize = img.width * img.channels;
    std::vector<unsigned char> tempRow(rowSize);
    for (int y = 0; y < img.height / 2; ++y) {
      unsigned char *top = img.imageData.data() + y * rowSize;
      unsigned char *bottom = img.imageData.data() + (img.height - 1 - y) * rowSize;
      memcpy(tempRow.data(), top, rowSize);
      memcpy(top, bottom, rowSize);
      memcpy(bottom, tempRow.data(), rowSize);
    }
  }

  Image ImageManager::loadPNG(const char *path) {
    FILE *fp = fopen(path, "rb");
    if (!fp) {
      throw std::runtime_error(std::format("Failed to open image: {}", path));
    }

    png_byte header[8];
    if (fread(header, 1, 8, fp) != 8) {
      fclose(fp);
      throw std::runtime_error(std::format("Failed to read PNG header: {}", path));
    }
    if (png_sig_cmp(header, 0, 8)) {
      fclose(fp);
      throw std::runtime_error(std::format("Not a PNG file: {}",path));
    }

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
      // PNG Read error
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

    unsigned int channels = png_get_channels(png_ptr, info_ptr);

    std::vector<png_bytep> row_pointers(height);
    std::vector<unsigned char> image_data(height * width * channels);
    for (size_t i = 0; i < height; ++i) {
      row_pointers[i] = &image_data[i * width * channels];
    }

    png_read_image(png_ptr, row_pointers.data());

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    fclose(fp);

    return Image{image_data, width, height, channels};
  }
}
