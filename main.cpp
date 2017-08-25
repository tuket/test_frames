#include <iostream>
#include <vector>
#include <fstream>
#include <SDL.h>
#include <glad/glad.h>

using namespace std;

// the application will close after this amount of time
const float MILISECONDS_TO_CLOSE = 10 * 1000;

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_Window* window =
		SDL_CreateWindow(
			"tracer",
			100, 100,
			800, 600,
			SDL_WINDOW_OPENGL
		);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	// SDL_GL_SetSwapInterval(1);	// this line mitigates the problem but just slightly

	if (!gladLoadGL())
	{
		cout << "gladLoadGL failed" << endl;
	}

	const GLubyte *oglVersion = glGetString(GL_VERSION);
	std::cout << "This system supports OpenGL Version: " << oglVersion << std::endl;
	const GLubyte *gpuVendor = glGetString(GL_VENDOR);
	std::cout << "Graphics card: " << gpuVendor << std::endl;

	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

	vector<unsigned> deltas;
	deltas.reserve(10 * MILISECONDS_TO_CLOSE);

	static unsigned firstTime, prevTime, curTime;
	firstTime = prevTime = curTime = SDL_GetTicks();
	while (true)
	{
		// compute delta time
		curTime = SDL_GetTicks();
		unsigned dt = curTime - prevTime;
		prevTime = curTime;
		deltas.push_back(dt);

		// close the application after some time
		if (curTime - firstTime > MILISECONDS_TO_CLOSE) break;

		// handle closing events
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT) break;
		}

		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(window);
	}

	// save recorded deltas to a file
	fstream f("out.txt", ios::out | ios::trunc);
	for (unsigned dt : deltas) f << dt << endl;
	f << flush;
	f.close();

	return 0;
}