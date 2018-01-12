#pragma once
#include <string>
#include <GL/glew.h>
class GLSLProgram
{
private:
	int _numAttributes;
	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
public:
	GLSLProgram();
	~GLSLProgram();

	GLuint getUniformLocation(const std::string &uniformName);

	void addAttribute(const std::string &attributeName);
	void compileShader(const std::string &filePath,
		GLuint id);
	void compileShaders(const std::string& vertexShaderFilePath,
		                const std::string& fragmentShaderFilePath);
	void linkShaders();
	void use();
	void unuse();
	
};

