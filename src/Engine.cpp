#include <include/Engine.hpp>
#include <include/Exception.hpp>
#include <include/Logger.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
		throw util::Exception("Failed to load SDL: %s.", SDL_GetError());
	}
	
	util::Log(util::Debug) << "Initialized SDL.";
	
	this->window = SDL_CreateWindow("GSG Framework", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	
	if (this->window == nullptr)
	{
		throw util::Exception("Failed to create an SDL window: %s.", SDL_GetError());
	}
	
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
}