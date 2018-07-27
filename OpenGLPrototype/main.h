#pragma once

void renderLoop();
void keyboardFunc(unsigned char key, int x, int y);
void changeViewport(int width, int height);
GLuint makeShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID);
GLuint makeShader(const char* shaderSource, GLushort shaderType);
static char* readFile(const char* filename);
int main(int argc, char ** argv);
