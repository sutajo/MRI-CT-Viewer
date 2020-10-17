#include "app.hpp"
#include "GLUtils.hpp"

#include "quad.hpp"

#include <math.h>
#include <string>

App::App()
{
	Init();
}


App::~App()
{
	
}

void App::Init()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK); // OR GL_FRONT

	camera.SetView(glm::vec3( 0,  0,  5),
				   glm::vec3( 0,  0,  0),
				   glm::vec3( 0,  1,  0));

	cube.prepareShader(cubeShader);
	quad.prepareShader(quadShader);
}

void App::Update()
{
	static Uint32 last_time = SDL_GetTicks();
	float delta_time = (SDL_GetTicks() - last_time) / 1000.0f;

	camera.Update(delta_time);

	last_time = SDL_GetTicks();
}

const glm::mat4 id = glm::mat4(1.0f); 

void App::Render()
{
	frontFaceFrameBuffer.useAsRenderTarget([this]{
		glClearColor(0.125f, 0.25f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cube.render(cubeShader, camera.GetViewProj() * glm::translate(glm::mat4(1.0f), glm::vec3(2,0,0)));
	});

	backFaceFrameBuffer.useAsRenderTarget([this]{
		glClearColor(0.5f, 0.25f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glCullFace(GL_FRONT);
		cube.render(cubeShader, camera.GetViewProj() * glm::translate(glm::mat4(1.0f), glm::vec3(2,0,0)));
		glCullFace(GL_BACK);
	});

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	quadShader.use([this](Shader &shader){
		shader.bindUniformTexture("texImage", frontFaceFrameBuffer.getColorBuffer(0), 0);
		shader.bindUniformMatrix4("MVP", glm::scale(glm::translate(id, glm::vec3(-0.5f, 0, 0)), glm::vec3(0.5,1,1)));
		quad.render(shader);
	});

	quadShader.use([this](Shader &shader){
		shader.bindUniformTexture("texImage", backFaceFrameBuffer.getColorBuffer(0), 0);
		shader.bindUniformMatrix4("MVP", glm::scale(glm::translate(id, glm::vec3(0.5f, 0, 0)), glm::vec3(0.5,1,1)));
		quad.render(shader);
	});
}

void App::KeyboardDown(SDL_KeyboardEvent& key)
{
	camera.KeyboardDown(key);
}

void App::KeyboardUp(SDL_KeyboardEvent& key)
{
	camera.KeyboardUp(key);
}

void App::MouseMove(SDL_MouseMotionEvent& mouse)
{
	camera.MouseMove(mouse);
}

void App::MouseDown(SDL_MouseButtonEvent& mouse)
{
}

void App::MouseUp(SDL_MouseButtonEvent& mouse)
{
}

void App::MouseWheel(SDL_MouseWheelEvent& wheel)
{
}

void App::Resize(int width, int height)
{
	glViewport(0, 0, width, height);

	camera.Resize(width, height);
}