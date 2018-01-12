/* detectOS.h - This header file checks the OS of a given system and includes the appropriate libraries for OpenGL as a result. */
/* Note that this implementation only supports some versions of Linux and Windows. It has not been configured for MacOS. */
#if defined(__linux__)
#include <GL/gl.h>
#include <GL/glu.h>
#include <opengl32.lib>
#include <glu32.lib>
#elif defined(_WIN32) || defined(_WIN64)
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glew.h>
#include <Windows.h>
#endif