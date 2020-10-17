#ifndef _CUBE_
#define _CUBE_

#include <GL/glew.h>

#include "renderable.hpp"
#include "shader.hpp"
#include "VertexArrayObject.hpp"
#include "BufferObject.hpp"

class Cube : public Renderable {
private:
  VertexArrayObject vao;
  ArrayBuffer       vertex_buffer;
  ArrayBuffer       color_buffer;
  IndexBuffer       ibo;

public:
  Cube();
  ~Cube(){}

  virtual void prepareShader(Shader&) override;
  virtual void render(Shader&, glm::mat4) override;
};

#endif