#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "GLSLProgram.h"

enum class GameState { PLAY, L_CLICK, EXIT };

class Window
{
private:
	bool _isCorrect; //If one of the hidden tiles.

	int _screenWidth;
	int _screenHeight;

	GameState _gameState = GameState::PLAY;
	GLSLProgram _colorProgram;
	SDL_Window* _window;

	//Methods
	bool checkTile();
	void drawGame();
	void drawBoard();
	void gameLoop();
	void initSystems();
	void initShaders();
	void processInput();

public:
	Window();
	~Window();

	void run();
};

