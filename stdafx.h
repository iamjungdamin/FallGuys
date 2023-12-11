#pragma once

#include "OpenGL/glew.h"
#include "OpenGL/freeglut.h"
#include "OpenGL/glm/ext.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")

extern GLint winWidth;
extern GLint winHeight;

std::string ReadFile(std::string fileName);
GLuint CreateShaderProgram(std::string vertexFile, std::string fragmentFile);
GLuint CompileShader(std::string fileName, GLenum shaderType);
std::vector<glm::vec3> ReadObjWithRColorNormal(std::string fileName, glm::vec3 fixedColor);
