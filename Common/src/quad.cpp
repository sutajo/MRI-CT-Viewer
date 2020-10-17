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

#include "quad.hpp"

const glm::vec3 Quad::vertices[4] = 
            {{ 1, -1, 0},
             {-1, -1, 0},
             {-1,  1, 0},
             { 1,  1, 0}};

/*

(-1, 1) ------- (1,  1)



(-1,-1) ------- (1, -1)

*/

const glm::vec2 Quad::texCoords[4] = 
            {{1.0f, 0.0f},
			       {0.0f, 0.0f},
			       {0.0f, 1.0f},
			       {1.0f, 1.0f}};

const GLubyte Quad::indices[6] = 
            {3,1,0,
             1,3,2};

Quad::Quad(){
  	positionBuffer.BufferData(vertices);

	texCoordBuffer.BufferData(texCoords);

	indexBuffer.BufferData(indices);

	vao.Init(
		{
			{ CreateAttribute<0, glm::vec3>, positionBuffer },
			{ CreateAttribute<1, glm::vec2>, texCoordBuffer }
		},
		indexBuffer
	);
}

void Quad::prepareShader(Shader& shader)
{
	shader.bindAttribLocation(0, "position");
    shader.bindAttribLocation(1, "texCoord");
}

void Quad::render(Shader& shader, glm::mat4 transforamtion){
  vao.Bind();

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

  vao.Unbind();
}
