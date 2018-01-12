#include "Window.h"
#include <iostream>
#include <string>
#include "GLSLProgram.h"
#include "Error.h"


Window::Window() : _isCorrect(false),
	               _screenWidth(1024),
                   _screenHeight(768),
	               _window(nullptr),
	               _gameState(GameState::PLAY)	               
{/* Initialization list for GPU optimizations. */}

Window::~Window() //Not sure these destructors need to be here.
{
}

void Window::drawBoard()
{
	
}

void Window::drawGame()
{

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	//Generate the board.
	drawBoard();

	_colorProgram.unuse();

	SDL_GL_SwapWindow(_window);
}

void Window::gameLoop() 
{
	while (_gameState != GameState::EXIT) 
	{
		processInput();

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
	_colorProgram.compileShaders("C:\\Users\\John\\Desktop\\WIP\\Software Engineering\\GUI\\Shaders\\colorShading.vert", 
		"C:\\Users\\John\\Desktop\\WIP\\Software Engineering\\GUI\\Shaders\\colorShading.frag");
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
				_isCorrect = checkTile();
			break;
		}
	}
}

void Window::run()
{
	initSystems(); //Opens the Window and sets up OpenGL.
	gameLoop();
}