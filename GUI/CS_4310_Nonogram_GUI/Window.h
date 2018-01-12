#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "GLSLProgram.h"

enum class GameState { PLAY, L_CLICK, EXIT };

class Window
{
private:
	int _screenWidth;
	int _screenHeight;
	GameState _gameState = GameState::PLAY;
	GLSLProgram _colorProgram;
	SDL_Window* _window;
	void drawGame();
	void gameLoop();
	void initSystems();
	void initShaders();
	void processInput();

public:
	Window();

	void run();
};

