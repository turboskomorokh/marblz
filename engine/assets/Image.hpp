//
// Created by turbo on 28.06.25.
//

#ifndef MARBL_IMAGE_HPP
#define MARBL_IMAGE_HPP

#include <vector>

namespace marblz::assets {
  struct Image {
    std::vector<unsigned char> imageData;
    unsigned int width;
    unsigned int height;
    unsigned int channels;
  };
}
#endif //MARBL_IMAGE_HPP
