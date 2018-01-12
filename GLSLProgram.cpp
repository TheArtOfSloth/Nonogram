#include "GLSLProgram.h"
#include "Error.h"
#include <string>
#include <fstream>
#include <vector>


GLSLProgram::GLSLProgram() : _numAttributes(0),
							 _programID(0), 
							_vertexShaderID(0), 
							_fragmentShaderID(0)
{ /*Initialization list*/ }

void GLSLProgram::addAttribute(const std::string &attributeName)
{
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

void GLSLProgram::compileShader(const std::string &filePath, GLuint id)
{
	std::ifstream vertexFile(filePath, std::ifstream::in);
	if (vertexFile.fail())
		fatalError("Failed to open " + filePath);

	std::string fileContents = "";
	std::string line;

	while (std::getline(vertexFile, line))
	{
		fileContents += line + "\n";
	}

	vertexFile.close();
	//This is for typecasting a String to a C-string
	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);

	GLint success = 0;
	//iv = int variable. OpenGL error handler.
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		//
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
		//
		glDeleteShader(id);

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shader " + filePath + " failed to compile");

		return;
	}
}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath,
	                             const std::string& fragmentShaderFilePath) 
{
	//We need to create a program object for the linker. 
	_programID = glCreateProgram();
	//Create shader objects for rendering.
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0)
		fatalError("Vertex shader failed to be created");

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0)
		fatalError("Fragment shader failed to be created");

	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);
	
}

void GLSLProgram::linkShaders() 
{
	//Here's where our union occurs.
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);
	glLinkProgram(_programID);

	GLint isLinked = 0;
	glGetProgramiv(_programID,GL_LINK_STATUS, (int*)&isLinked);
	//Error handler
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);
		//Delete the program object if a failure occurred.
		glDeleteProgram(_programID);
		//Delete shader objects as well to prevent memory leaks.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shaders failed to link");
	}
	//Detach shaders after successful linkage to avoid glitches when re-rendering the pane.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	//Same as with potential errors, clear up the memory for re-rendering.
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}