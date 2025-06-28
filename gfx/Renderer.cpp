//
// Created by turbo on 28.06.25.
//

#include <spdlog/spdlog.h>

#include "Renderer.hpp"

void GLESRenderer::init() {
  spdlog::info("GLESRenderer initializing.");
}
void GLESRenderer::load() {}
void GLESRenderer::finalize() {}

void GLRenderer::init() {
  spdlog::info("GLRenderer initializing.");
}

void GLRenderer::finalize() {}

void GLRenderer::load() {}
