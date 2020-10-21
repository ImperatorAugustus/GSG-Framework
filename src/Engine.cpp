#include <include/Engine.hpp>
#include <include/Exception.hpp>
#include <include/Logger.hpp>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

eng::Engine::Engine()
{
	this->window = nullptr;
	this->running = false;
	
	util::Log(util::Info) << "Engine started.";
}

eng::Engine::~Engine()
{
}

void eng::Engine::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		throw util::Exception("Failed to load SDL: %s", SDL_GetError());
	}
	
	this->window = SDL_CreateWindow("GSG Framework", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	
	if (this->window == nullptr)
	{
		throw util::Exception("Failed to create an SDL window: %s", SDL_GetError());
	}
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	
	this->glcontext = SDL_GL_CreateContext(this->window);
	if (this->glcontext == NULL)
	{
		throw util::Exception("Failed to create an OpenGL context: %s", SDL_GetError());
	}
	
	util::Log(util::Debug) << "Initialized SDL.";
	
	int vmaj, vmin;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &vmaj);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &vmin);
	
	SDL_GL_SetSwapInterval(1);
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	glCullFace(GL_BACK);
	
	glDepthFunc(GL_LESS);
	
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		throw util::Exception("Failed to initialize OpenGL: %s", glewGetErrorString(error));
	}
	
	util::Log(util::Debug) << "Initialized OpenGl version " << vmaj << "." << vmin;
	
	this->running = true;
}

void eng::Engine::run()
{
	init();
	
	int ticks = 0, frames = 0;
	int lastTick = SDL_GetTicks();
	double silentTime = 0.0;
	const double timePerTick = 1.0 / 60.0;
	
	while (this->running)
	{
		// simplistic code to stabilize the tick loop and prevent CPU overload.
		int now = SDL_GetTicks();
		int delta = (now - lastTick);
		lastTick = now;
		
		silentTime += delta / 1000.0;
		bool ticked = false;
		
		while (silentTime >= timePerTick)
		{
			silentTime -= timePerTick;
			tick();
			ticks++;
			ticked = true;
			
			if (ticks % 60 == 0)
			{
				util::Log(util::Debug) << frames << " fps.";
				frames = 0;
			}
		}
		
		if (ticked)
		{
			render();
			frames++;
		}
		else
		{
			SDL_Delay(1);
		}
	}
	
	quit();
}

void eng::Engine::quit()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void eng::Engine::tick()
{
	// polling SDL events.
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			this->running = false;
		}
	}
	
	// tick logic below here.
}

void eng::Engine::render()
{
	// render logic
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Here we do things.
	
	SDL_GL_SwapWindow(this->window);
}