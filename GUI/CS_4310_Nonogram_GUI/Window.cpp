#include "Window.h"
#include <iostream>
#include <string>
#include "GLSLProgram.h"
#include "Error.h"

Window::Window() : _screenWidth(800),
                   _screenHeight(600),
     	           _window(nullptr),
                   _gameState(GameState::PLAY)
{/* Initialization list for GPU optimizations. */}

void Window::drawGame()
{
	int row = _screenWidth;
	int col = _screenHeight;
	//Clear the buffer to prevent any side effects.
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES); //Open pipe to schedule the GPU instructions.
	for (int i = 0; i < row; i++)
	{
		glVertex3f(-1, i * 0.1 - 1, 1);
		glVertex3f(col, i * 0.1 + 1, 1);
		
	}
	for (int j = 0; j < col; j++)
	{
		glVertex3f(j * 0.1 - 1, -1, 1);
		glVertex3f(j * 0.1 + 1, row, 1);
	}

	glEnd(); //Close the pipe
	glFlush();   //Write the contents of the buffer out to the GPU driver.
	SDL_GL_SwapWindow(_window);
}

void Window::gameLoop() 
{
	while (_gameState != GameState::EXIT) 
	{
		//Call polling loop for user events. Terminate when exit flag is raised.
		processInput();
		//Call the rendering function to cascade the window.
		drawGame();
	}
}

void Window::initSystems() 
{
	//Initialize SDL for the window object.
	SDL_Init(SDL_INIT_EVERYTHING);
	//Explain SDL_CreateWindow params here.
	_window = SDL_CreateWindow("Nonogram", SDL_WINDOWPOS_CENTERED,
			                   SDL_WINDOWPOS_CENTERED, _screenWidth,
			                   _screenHeight, SDL_WINDOW_OPENGL);
	
	if (_window == nullptr) {
		fatalError("SDL Window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("SDL_GL context could not be created!");
	}

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fatalError("Could not initialize glew!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//What color to paint the screen when re-rendering.
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	
	initShaders();
}

void Window::initShaders()
{
	//CHANGE FILEPATHS ON FINAL BUILD -> VS opens Solutions file in a private directory. Shaders path DNE there.
	_colorProgram.compileShaders("C:\\Users\\John\\Desktop\\WIP\\Software Engineering\\Nonogram\\GUI\\Shaders\\colorShading.vert", 
		                         "C:\\Users\\John\\Desktop\\WIP\\Software Engineering\\Nonogram\\GUI\\Shaders\\colorShading.frag");
	_colorProgram.addAttribute("vertexPos");
	_colorProgram.linkShaders();
}

void Window::processInput() 
{
	SDL_Event input;

	//Captures any user events.
	while (SDL_PollEvent(&input)) 
	{
		
		switch (input.type) 
		{
			case SDL_QUIT: 
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEBUTTONDOWN:
				_gameState = GameState::L_CLICK;
				std::cout << "Mouse down\n";
				break;
			case SDL_MOUSEBUTTONUP:
				std::cout << "Mouse up\n";
				break;
			case SDL_MOUSEMOTION:

				break;
		}
	}
}

void Window::run()
{
	initSystems(); //Opens the Window and sets up OpenGL.
	gameLoop();
}