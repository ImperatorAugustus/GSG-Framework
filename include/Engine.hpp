#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL2/SDL.h>

namespace eng
{
	class Engine
	{
	public:
		Engine();
		~Engine();
		
		void init();
		void run();
		void quit();
		
	private:
		void tick();
		void render();
		
	private:
		SDL_Window* window;
		bool running;
	};
}

#endif // ENGINE_HPP
