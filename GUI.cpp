//#include "detectOS.h" //Remove this if the GUI works on Linux!
#include <Windows.h> 
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Window.h"
#include <iostream>
#include "Error.h"

int main(int ac, char** argv) {
	Window window;

	window.run();

	return 0;
}
//This is mostly a driver for testing. Import window into main.cpp of project.