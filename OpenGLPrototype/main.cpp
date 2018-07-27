#include <GL\glew.h>
#include "main.h"
#include <glm\glm.hpp>
#include <GL\freeglut.h>
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
#include "Primitive.h"

extern int totalVerticesToRender;

static char* readFile(const char* filename) {
	FILE* filepoint;
	errno_t err = fopen_s(&filepoint, filename, "r");
	if (err != 0) {
		throw std::runtime_error("autistic screeching");
	}
	else {
		fseek(filepoint, 0, SEEK_END);
		long file_length = ftell(filepoint);
		fseek(filepoint, 0, SEEK_SET);
		char* contents = new char[file_length + 1];
		for (int i = 0; i < file_length + 1; i++) {
			contents[i] = 0;
		}
		fread(contents, 1, file_length, filepoint);
		contents[file_length + 1] = '\0';
		fclose(filepoint);
		return contents;
	}
}

GLuint makeShader(const char* shaderSource, GLushort shaderType) {
	GLuint shaderObjectID = glCreateShader(shaderType);
	glShaderSource(shaderObjectID, 1, (const GLchar**)&shaderSource, NULL); //no need to explicitly tell opengl the length of shadersource; our string is null terminated so it's fine
	glCompileShader(shaderObjectID);
	GLint compileStatus; //opengl was made with client-server architecture in mind; compileStatus is a network efficient way of communicating long strings
	glGetShaderiv(shaderObjectID, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE) {
		GLint infoLogLength;
		glGetShaderiv(shaderObjectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];
		GLsizei gay;
		glGetShaderInfoLog(shaderObjectID, infoLogLength, &gay, buffer);
		std::cout << buffer << std::endl;
		delete[] buffer;
	}
	return shaderObjectID;
}

GLuint makeShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID) {
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	GLint linkStatus; //opengl was made with client-server architecture in mind; compileStatus is a network efficient way of communicating long strings
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE) {
		GLint infoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];
		GLsizei gay;
		glGetProgramInfoLog(programID, infoLogLength, &gay, buffer);
		std::cout << buffer << std::endl;
		delete[] buffer;
	}
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	return programID;
}

bool bypassSelfTrigger = false;
void changeViewport(int width, int height) {
	if (bypassSelfTrigger) {
		bypassSelfTrigger = false;
		return;
	}
	if (width < 640){
		bypassSelfTrigger = true;
		width = 640;
	}
	if (height < 360) {
		bypassSelfTrigger = true;
		height = 360;
	}
	if(bypassSelfTrigger)
		glutReshapeWindow(width, height);
	glViewport(0, 0, width, height);
}

void keyboardFunc(unsigned char key, int x, int y) {
	
}

void printMatrix(glm::mat4 gay) {
	std::cout << gay[0][0] << ',' << gay[1][0] << ',' << gay[2][0] << ',' << gay[3][0] << std::endl;
	std::cout << gay[0][1] << ',' << gay[1][1] << ',' << gay[2][1] << ',' << gay[3][1] << std::endl;
	std::cout << gay[0][2] << ',' << gay[1][2] << ',' << gay[2][2] << ',' << gay[3][2] << std::endl;
	std::cout << gay[0][3] << ',' << gay[1][3] << ',' << gay[2][3] << ',' << gay[3][3] << std::endl;
}

GLuint programID;
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(720, 720);
	glutCreateWindow("skidnology");
	GLenum err = glewInit(); //sets up function pointers for all the opengl functions called
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	glEnable(GL_DEPTH_TEST);
	char* vertexShaderSourceCode = readFile("vertexShader.vsh");
	char* fragmentShaderSourceCode = readFile("fragmentShader.fsh");
	GLuint vertShaderID = makeShader(vertexShaderSourceCode, GL_VERTEX_SHADER);
	GLuint fragShaderID = makeShader(fragmentShaderSourceCode, GL_FRAGMENT_SHADER);
	programID = makeShaderProgram(vertShaderID, fragShaderID); //fat gay global hmmm
	glUseProgram(programID);

	//Primitive* cube = new Primitive(ShapeTypes::Cube);
	//GLuint vertBufferID;
	//glGenBuffers(1, &vertBufferID); //a vertex buffer object is generated and the arbitrary ID of that vertex buffer object is assigned to the address vertBufferID
	//glBindBuffer(GL_ARRAY_BUFFER, vertBufferID); //more abstractions!!; this describes what kind of VBO vertBufferID is and connects 
	//											 //number of bytes of VRAM (GPU could possibly use something else) to allocate, the starting address of our array, optimization hint for GPU internals
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*cube->verticesToStore, cube->vertices, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0); //position; 0 is arbitrary slot for new attribute of every vertex; opengl will only assume first attribute describes a position
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	//glEnableVertexAttribArray(1); //color; 1 is arbitrary slot for new attribute of every vertex; fragment shader code has to be written to utilize this attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); //the last argument defines offset until the first appearance of the attribute; 3 floats in

	//GLuint indBufferID;
	//glGenBuffers(1, &indBufferID);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufferID);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*cube->verticesToRender, cube->indices, GL_STATIC_DRAW);
	//delete cube; //this line will make the cube invisible?? all geometry data should be stored on gpu now?
	Primitive* cube = new Primitive(ShapeTypes::Cube);
	GLuint vertBufferID;
	glGenBuffers(1, &vertBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*cube->verticesToStore, cube->vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	GLuint indBufferID;
	glGenBuffers(1, &indBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*cube->verticesToRender, cube->indices, GL_STATIC_DRAW);
	delete cube; //this line will make the cube invisible?? all geometry data should be stored on gpu now?

	glutReshapeFunc(changeViewport);
	glutDisplayFunc(renderLoop);
	glutKeyboardFunc(keyboardFunc);

	glutMainLoop();
	glUseProgram(0);
	glDeleteProgram(programID);
	return 0;
}

float degFat;
void renderLoop() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	degFat = (degFat + 1.0f) == 360.0f ? 0.0f : degFat + 1.0f;
	glm::mat4 projectionM = glm::perspective(glm::radians(70.0f), (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 10.0f);
	glm::mat4 projectionTranslationM = glm::translate(projectionM, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 transformationM = glm::rotate(projectionTranslationM, glm::radians(degFat), glm::vec3(0.0f, 1.0f, 0.0f)); //rotate object around its center first before translation
																														//projection * translation * rotation
	GLint transformationMatrixLoc = glGetUniformLocation(programID, "transformationMatrix");
	glUniformMatrix4fv(transformationMatrixLoc, 1, GL_FALSE, &transformationM[0][0]);
	glDrawElements(GL_TRIANGLES, Primitive::totalVerticesToRender, GL_UNSIGNED_SHORT, 0);
	glutSwapBuffers();
	glutPostRedisplay();
}