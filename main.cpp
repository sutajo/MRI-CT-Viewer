#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>
#include <sstream>

#include "app.hpp"

class SDL_Guard
{
	SDL_Window    *window = nullptr;
	SDL_GLContext  context = nullptr;

	void init()
	{
		std::stringstream error_msg;

		if ( SDL_Init( SDL_INIT_VIDEO ) == -1 )
		{
			error_msg << "[SDL_Init] " << SDL_GetError() << std::endl;
			throw error_msg;
		}
				

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,         32);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,		1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          24);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  4);

		window = SDL_CreateWindow( "MRI/CT 3D Visualizer",
								100,
								100,
								App::InitialWindowWidth,
								App::InitialWindowHeight,
								SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);		

		if (window == nullptr)
		{
			error_msg << "[SDL_CreateWindow] " << SDL_GetError() << std::endl;
			throw error_msg;
		}

		context = SDL_GL_CreateContext(window);
		if (context == nullptr)
		{
			error_msg << "[SDL_GL_CreateContext]" << SDL_GetError() << std::endl;
			throw error_msg;
		}	

		SDL_GL_SetSwapInterval(1);

		GLenum error = glewInit();
		if ( error != GLEW_OK )
		{
			error_msg << "[glewInit] An error occured during GLEW initialization." << std::endl;
			throw error_msg;
		}

		int glVersion[2] = {-1, -1}; 
		glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]); 
		glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]); 

		if ( glVersion[0] == -1 && glVersion[1] == -1 )
		{
			SDL_GL_DeleteContext(context);
			SDL_DestroyWindow( window );
			error_msg << "[glGetIntegerv(GL_VERSION)] Invalid version." << std::endl;
			throw error_msg;
		}

		std::cout << "Running OpenGL " << glVersion[0] << "." << glVersion[1] << std::endl;
	}

	public:
		SDL_Guard() {
			init();
		}

		~SDL_Guard(){  
			if (context != nullptr) 
				SDL_GL_DeleteContext(context);
			
			if (window != nullptr)
				SDL_DestroyWindow(window);

			SDL_Quit();	
		}

		SDL_Window*   getWindow()  { return window;  }
		SDL_GLContext getContext() { return context; }
};

int main( int argc, char* args[] )
{
	try
	{
		SDL_Guard sdl;

		bool quit = false;

		SDL_Event ev;
		
		App app;

		while (!quit)
		{
			while ( SDL_PollEvent(&ev) )
			{
				switch (ev.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					if ( ev.key.keysym.sym == SDLK_ESCAPE )
						quit = true;
					app.KeyboardDown(ev.key);
					break;
				case SDL_KEYUP:
					app.KeyboardUp(ev.key);
					break;
				case SDL_MOUSEBUTTONDOWN:
					app.MouseDown(ev.button);
					break;
				case SDL_MOUSEBUTTONUP:
					app.MouseUp(ev.button);
					break;
				case SDL_MOUSEWHEEL:
					app.MouseWheel(ev.wheel);
					break;
				case SDL_MOUSEMOTION:
					app.MouseMove(ev.motion);
					break;
				case SDL_WINDOWEVENT:
					if ( ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED )
					{
						app.Resize(ev.window.data1, ev.window.data2);
					}
					break;
				}
			}

			app.Update();
			app.Render();

			SDL_GL_SwapWindow(sdl.getWindow());
		}
	}
	catch(std::string &msg)
	{
		std::cerr << "An exception occured." << std::endl << msg << std::endl;
		return EXIT_FAILURE;
	}
	catch(std::exception &e)
	{
		std::cerr << "An exception occured." << std::endl << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch(...)
	{
		std::cerr << "Unknown exception occured." << std::endl;
		return EXIT_FAILURE;
	}

	return 0;
}