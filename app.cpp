#include "app.hpp"
#include "GLUtils.hpp"

#include <math.h>
#include <string>
#include <cstdint>
#include <fstream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>


uint32_t rgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (a << 24) | (b << 16) | (g << 8) | r;
}

std::vector<uint8_t> readFile(std::string path)
{
	std::cout << "Reading file" << std::endl;

	std::vector<uint8_t> inputVector;
	std::ifstream input(path, std::ios::binary);
	if(!input.is_open())
		std::cout << "File not found" << std::endl;
	while(!input.eof())
	{
		uint8_t r = input.get();
		inputVector.push_back(r);
	}

	std::cout << "Done reading file. Vector size: " << inputVector.size() << std::endl;

	return std::move(inputVector);
}

App::App()
{
	Init();
}


App::~App()
{
	
}

inline bool inRange(int val, int lower, int upper)
{
	return lower <= val && val <= upper;
}

/*
void App::InitSphereVolume()
{
	const int Width = 301;
	const int Height = 324;
	const int Depth = 56;

	sphereVolume.initialize(Width, Height, Depth);

	std::vector<uint8_t> data = readFile("lobster.raw");

	sphereVolume.setData(&data[0]);
}
*/

void App::InitSphereVolume()
{
	const int Size = 128;

		sphereVolume.initialize(Size, Size, Size);

		std::vector<uint8_t> data(Size*Size*Size);

		for(auto k = 0; k < Size; ++k)
		for(auto j = 0; j < Size; ++j)
			for(auto i = 0; i < Size; ++i)
			data[k*Size*Size+ j*Size+i] = 0;

		for(auto k = 8; k < Size-8; ++k)
		for(auto j = 8; j < Size-8; ++j)
			for(auto i = 8; i < Size-8; ++i)
			data[k*Size*Size+ j*Size+i] = 255;

		sphereVolume.setData(&data[0]);
}

void App::Init()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK); // OR GL_FRONT

	camera.SetView(glm::vec3( 0,  0.5,  2),
				   glm::vec3( 0.5,  0.5,  0.5),
				   glm::vec3( 0,  1,  0));

	cube.prepareShader(cubeShader);
	quad.prepareShader(quadSimpleShader);
	quad.prepareShader(quadShader);

	InitSphereVolume();
}

static Uint32 last_time = SDL_GetTicks();

void App::Update()
{
	float now = SDL_GetTicks();
	float delta_time = (now - last_time) / 1000.0f;

	camera.Update(delta_time);

	last_time = now;
}

const glm::mat4 id = glm::mat4(1.0f);

void App::Render()
{
	glm::mat4 Composed_mvp = camera.GetViewProj();
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(Composed_mvp, scale, rotation, translation, skew, perspective);

	const glm::mat4 Rot = camera.GetProj() * glm::toMat4(rotation);

	frontFaceFrameBuffer.useAsRenderTarget([this, &Composed_mvp, Rot]{
		glClearColor(0.125f, 0.25f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cubeShader.enable();
		cubeShader.bindUniformMatrix4("Rotation", Rot);
		cube.render(cubeShader, Composed_mvp);
	});

	backFaceFrameBuffer.useAsRenderTarget([this, &Composed_mvp, Rot]{
		glClearColor(0.125f, 0.20f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glCullFace(GL_FRONT);
		cubeShader.enable();
		cubeShader.bindUniformMatrix4("Rotation", Rot);
		cube.render(cubeShader, Composed_mvp);
		glCullFace(GL_BACK);
	});

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	quadShader.use([this](Shader &shader){
		shader.bindUniformTexture("texImage", frontFaceFrameBuffer.getColorBuffer(0), 0);
		shader.bindUniformTexture("backTexture", backFaceFrameBuffer.getColorBuffer(0), 1);
		shader.bindUniformTexture3D("volume", sphereVolume.getTextureHandle(), 2);
		shader.bindUniformMatrix4("MVP", glm::scale(glm::translate(id, glm::vec3(0, -0.5f, 0)), glm::vec3(0.5,0.5,1)));
		quad.render(shader);
	});

	quadSimpleShader.use([this](Shader &shader){
		shader.bindUniformTexture("texImage", frontFaceFrameBuffer.getColorBuffer(0), 0);
		shader.bindUniformMatrix4("MVP", glm::scale(glm::translate(id, glm::vec3(-0.5f, 0.5f, 0)), glm::vec3(0.5,0.5,1)));
		quad.render(shader);
	});

	quadSimpleShader.use([this](Shader &shader){
		shader.bindUniformTexture("texImage", backFaceFrameBuffer.getColorBuffer(0), 0);
		shader.bindUniformMatrix4("MVP", glm::scale(glm::translate(id, glm::vec3(0.5f, 0.5f, 0)), glm::vec3(0.5,0.5,1)));
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