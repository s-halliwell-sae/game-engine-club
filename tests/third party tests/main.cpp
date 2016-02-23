/*TODO
	generic property sheet with all 3rd party deps included and linked etc.
	use each 3rd party lib in at least a hello world style to confirm that they are there and working

*/

//must include spdlog before jemalloc due to incompat custom version of stdint in jemalloc
#include <spdlog.h>

// This forces jemalloc to prepend all it's functions with je_
//	NB: the library must also be built with this flag
#define JEMALLOC_NO_RENAME
#include <jemalloc/jemalloc.h>
#include <cstdio>
#include <iostream>

#include <lua.hpp>
#include <glm.hpp>
#include <SDL.h>
#include <gl/glew.h>
#include <gl/GL.h>

#undef main

void jemallocTest(){
	void *p;

	#ifdef WIN32
	// If you use jemalloc through the static lib,
	// must be manual initialize jemalloc first.
	je_init();
	#endif

	p = je_malloc(128);
	if (p) {
		printf("malloc(%u) result ptr = 0x%016" PRIXPTR "\n\n", 128, (unsigned long)p);
		je_free(p);
	}

	p = je_malloc(256);
	if (p) {
		printf("malloc(%u) result ptr = 0x%016" PRIXPTR "\n\n", 256, (unsigned long)p);
		je_free(p);
	}

	#ifdef WIN32
	// Unload the jemalloc
	je_uninit();
	#endif
}

void LuaTest(){
	lua_State* L = lua_open();
	luaL_openlibs(L);
	luaL_dostring(L, "print(\"Hello World from Lua\")");
	lua_close(L);
	L = nullptr;
}

void HandleShaderCheck(GLuint shader)
{
	GLint hasFailed = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &hasFailed);
	if (hasFailed != GL_TRUE)
	{
		std::cout << "failed to compile vs\n";

		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
		std::exit(0);
	}
}

void SDLStartUp()
{
	std::cout << "SDL Test" << std::endl;
	//http://openme.gl/opengl-4-x-example-using-sdl2-and-glm/
	SDL_Window *mainwindow;
	SDL_GLContext maincontext;/* Our opengl context handle */

	if (SDL_Init(SDL_INIT_VIDEO) < 0) { /* Initialize SDL's Video subsystem */
		std::cout << "Unable to initialize SDL" << std::endl;
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

	GLenum rev;
	glewExperimental = GL_TRUE;
	rev = glewInit();

	if (GLEW_OK != rev){
		std::cout << "Error: " << glewGetErrorString(rev) << std::endl;
		exit(1);
	} else {
		std::cout << "GLEW Init: Success!" << std::endl;
	}

		  	  
	SDL_GL_SetSwapInterval(1);

	//simple shaders
	std::string vertShaderSource =
	{
		"#version 330\n"
		"layout(location = 0) in vec2 vertex2D;\n"
		"\n"
		"void main() {\n"
		"	vec3 position = vec3(vertex2D,0);\n"
		"	gl_Position = vec4(position, 1);\n"
		"}\n"
	};

	std::string fragShaderSource =
	{
		"#version 330\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"void main() {\n"
		//red pixels
		"	color = vec4(1,0,0, 1);\n"
		"}\n"
	};

	//create shaders and programs
	auto vs = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vsshaderSource = vertShaderSource.c_str();
	glShaderSource(vs, 1, (const GLchar**)&vsshaderSource, nullptr);
	glCompileShader(vs);
	HandleShaderCheck(vs);

	//TODO should check these actually worked
	


	auto fs = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fsshaderSource = fragShaderSource.c_str();
	glShaderSource(fs, 1, (const GLchar**)&fsshaderSource, nullptr);
	glCompileShader(fs);
	HandleShaderCheck(fs);

	auto shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);

	GLint haslinked = GL_TRUE;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &haslinked);
	if (haslinked != GL_TRUE)
	{
		std::cout << "failed to link vs and fs\n";
		std::exit(0);
	}
	
	auto vertexShaderLocation = glGetAttribLocation(shaderProgram, "vertex2D");

	glDeleteShader(vs);
	glDeleteShader(fs);

	//create VBOs

	GLuint vbo, ibo;
	GLfloat verts[] =
	{
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f,  0.5f,
		-0.5f,  0.5f
	};

	//set up indicies for triangle list
	GLuint indicies[] = { 0, 1, 2, 0, 2, 3 };

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0 /* position */);

	//Create VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), verts, GL_STATIC_DRAW);

	//Create IBO
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indicies, GL_STATIC_DRAW);

	//bind vbos, program and shader
	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(vertexShaderLocation);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(vertexShaderLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	std::cout << "Drawing a red square for a bit\n";
	//actually draw
	for (int i = 0; i < 60; i++)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		SDL_GL_SwapWindow(mainwindow);
	}

	//unbind
	glDisableVertexAttribArray(vertexShaderLocation);
	glUseProgram(NULL);

	//free VBOs
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &vao);

	//free programs

	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();
	std::cout << "SDL2 start up and shutdown complete\n";
}

int main(int argc, char *argv[]){
	glm::vec3 a(1,0,0),b(0,1,0);
	a = a + b;
	std::cout << "GLM a + b = (" << a.x << "," << a.y << "," << a.z << ")" << std::endl;

	LuaTest();

	jemallocTest();

	//test sdl by creating an ogl 4.x window
	SDLStartUp();

	auto console = spdlog::stdout_logger_mt("console");
	console->info("Welcome to spdlog!");
	return 0;
}
