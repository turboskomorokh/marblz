//
// Created by turbo on 28.06.25.
//

#ifndef MARBL_RENDERER_HPP
#define MARBL_RENDERER_HPP

#include <atomic>
#include <mutex>
#include <queue>

#include "IRenderable.hpp"

enum class RendererType {
  NONE,
  OpenGL,
  OpenGL_ES,
};

class IGLRenderer {
public:
  virtual void init() = 0;
  virtual void finalize() = 0;
  virtual void load() = 0;
private:
};

class GLRenderer : public IGLRenderer
{
  void init();
  void finalize();
  void load();

private:
  std::queue<IRenderable*> renderQueue;
  std::mutex renderQueueMutex;
};

class GLESRenderer : public IGLRenderer
{
  void init();
  void finalize();
  void load();
};



#endif //MARBL_RENDERER_HPP
