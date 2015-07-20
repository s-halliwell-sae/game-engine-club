/*TODO
	generic property sheet with all 3rd party deps included and linked etc.
	use each 3rd party lib in at least a hello world style to confirm that they are there and working

*/

#include "lua.hpp"
#include "glm.hpp"
#include "spdlog.h"
#include "SDL.h"
#undef main

void LuaTest()
{
	lua_State* L = lua_open();
	luaL_openlibs(L);
	luaL_dostring(L, "print(\"Hello World from Lua\")");
	lua_close(L);
	L = nullptr;
}

void SDLStartUp()
{
	//http://openme.gl/opengl-4-x-example-using-sdl2-and-glm/
	SDL_Window *mainwindow;
	SDL_GLContext maincontext;/* Our opengl context handle */

	if (SDL_Init(SDL_INIT_VIDEO) < 0) { /* Initialize SDL's Video subsystem */
		std::cout << "Unable to initialize SDL";
		return;
	}

	  	  /* Request opengl 4.4 context. */
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

	  	  /* Turn on double buffering with a 24bit Z buffer.
	     	 * You may need to change this to 16 or 32 for your system */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	  	  /* Create our window centered at 512x512 resolution */
	mainwindow = SDL_CreateWindow("3rd Party Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!mainwindow){ /* Die if creation failed */
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	  	  /* Create our opengl context and attach it to our window */
	maincontext = SDL_GL_CreateContext(mainwindow);

	//GLenum rev;
	//glewExperimental = GL_TRUE;
	//rev = glewInit();

	//if (GLEW_OK != rev){
	//std::cout << "Error: " << glewGetErrorString(rev) << std::endl;
	//exit(1);
	//} else {
	//std::cout << "GLEW Init: Success!" << std::endl;
	//}

		  	  /* This makes our buffer swap syncronized with the monitor's vertical refresh */

	SDL_GL_SetSwapInterval(1);

	/*bool quit = false;

	Initialize();
	Reshape(512, 512);

	SDL_Event event;

	while (!quit){

	Display();
	SDL_GL_SwapWindow(mainwindow);

	while (SDL_PollEvent(&event)){
	if (event.type == SDL_QUIT){
	quit = true;
	}
	}
	}

	Finalize();*/

	  	  /* Delete our opengl context, destroy our window, and shutdown SDL */
	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();
	std::cout << "SDL2 start up and shutdown complete\n";
}

int main(int argc, char *argv[])
{
	glm::vec3 a,b;

	a = a + b;

	LuaTest();

	//test sdl by creating an ogl 4.x window
	SDLStartUp();

	auto console = spdlog::stdout_logger_mt("console");
	console->info("Welcome to spdlog!");
	return 0;
}
