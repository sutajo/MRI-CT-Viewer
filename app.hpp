#pragma once

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"
#include "shader.hpp"
#include "cube.hpp"
#include "framebuffer.hpp"
#include "quad.hpp"

#include "VertexArrayObject.hpp"
#include "BufferObject.hpp"

class App
{
	public:
		App(void);
		~App(void);

		void Init();
		void Clean();

		void Update();
		void Render();

		void KeyboardDown(SDL_KeyboardEvent&);
		void KeyboardUp(SDL_KeyboardEvent&);
		void MouseMove(SDL_MouseMotionEvent&);
		void MouseDown(SDL_MouseButtonEvent&);
		void MouseUp(SDL_MouseButtonEvent&);
		void MouseWheel(SDL_MouseWheelEvent&);
		void Resize(int, int);

		static const int InitialWindowWidth  = 1280;
		static const int InitialWindowHeight = 720;
	protected:
		Camera camera;
		Shader cubeShader{"shaders/cube.vert", "shaders/cube.frag"};
		Cube   cube;
		Quad   quad;
		Shader quadShader{"shaders/quad.vert", "shaders/quad.frag"};

		const GLuint bufferWidth  = InitialWindowWidth;
		const GLuint bufferHeight = InitialWindowHeight;
		Framebuffer frontFaceFrameBuffer {bufferWidth, bufferHeight, 1};
		Framebuffer backFaceFrameBuffer  {bufferWidth, bufferHeight, 1};
};

