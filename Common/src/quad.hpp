/*
 *
 * Copyright © 2010-2011 Balázs Tóth <tbalazs@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef _QUAD_
#define _QUAD_

#include <GL/glew.h>

#include "renderable.hpp"
#include "shader.hpp"
#include "BufferObject.hpp"
#include "VertexArrayObject.hpp"

class Quad : public Renderable {
private:
  static const glm::vec3 vertices[4];
  static const glm::vec2 texCoords[4];
  static const GLubyte indices[6];

  VertexArrayObject vao;
  ArrayBuffer       positionBuffer;
  ArrayBuffer       texCoordBuffer;
  IndexBuffer       indexBuffer;

public:
  Quad();
  ~Quad(){}

  virtual void prepareShader(Shader&) override;
  virtual void render(Shader& shader, glm::mat4 transformation = glm::mat4(1.0f)) override;
};

#endif
