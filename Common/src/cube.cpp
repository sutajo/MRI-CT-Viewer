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

#include "cube.hpp"

const glm::vec3 vertices[8] = {
    { 0.0f,  0.0f,  1.0f},
    { 1.0f,  0.0f,  1.0f},
    { 0.0f,  1.0f,  1.0f},
    { 1.0f,  1.0f,  1.0f},
    { 0.0f,  0.0f,  0.0f},
    { 1.0f,  0.0f,  0.0f},
    { 0.0f,  1.0f,  0.0f},
    { 1.0f,  1.0f,  0.0f}
};

const glm::vec3 colors[8] = {
    glm::vec3(1, 0, 0),
    glm::vec3(0, 1, 0),
    glm::vec3(0, 0, 1),
    glm::vec3(0, 1, 0),
    glm::vec3(1, 0, 0),
    glm::vec3(0, 1, 0),
    glm::vec3(0, 0, 1),
    glm::vec3(0, 1, 0)
};

constexpr int indexCount = 14;

const GLushort indices[indexCount] = {
    0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
};

Cube::Cube(){
  vertex_buffer.BufferData(vertices);

	color_buffer.BufferData(colors);

	ibo.BufferData(indices);

	vao.Init(
		{
			{ CreateAttribute<0, glm::vec3>, vertex_buffer },
			{ CreateAttribute<1, glm::vec3>, color_buffer  }
		},
		ibo
	);
}

void Cube::prepareShader(Shader& shader)
{
  shader.bindAttribLocation(0, "vs_in_pos");
  shader.bindAttribLocation(1, "vs_in_col");
}

void Cube::render(Shader& shader, glm::mat4 transformation)
{
  shader.enable();
  vao.Bind();

  shader.bindUniformMatrix4("MVP", transformation);

  glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_SHORT, 0);

  vao.Unbind();
  shader.disable();
}
