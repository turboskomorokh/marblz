//
// Created by turbo on 28.06.25.
//

#ifndef MARBL_IMAGEMANAGER_HPP
#define MARBL_IMAGEMANAGER_HPP

#include "Image.hpp"

namespace marblz::assets {
  class ImageManager {
  public:
    static Image loadPNG(const char *path);
  };
}


#endif //MARBL_IMAGEMANAGER_HPP
