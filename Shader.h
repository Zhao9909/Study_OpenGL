#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	string vertexString;
	string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;//shader program ID
	void use();
	
private:
	void checkCompileErrors(unsigned int ID,std::string type);
};

