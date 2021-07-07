/*
Computacion Grafica [CG-2021-i]

Integrantes:
Mariangela Pacheco Delgado
Miguel Zegarra Castillo

*/

#include <iostream>
#include "Rubik.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <string>
#include <vector>
using namespace std;

vector<float> vertex = { 0.0f, 0.0f, 0.0f };
vector<float> vertexRubik;
float anguloX = 0, anguloY=0, anguloZ=0;
GLFWwindow* window;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
#include "Shaders.h"
#include "functions.h"
#include "Cube.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


point a = point(-cubeSize / 2.0, cubeSize / 2.0, -(cubeSize*0.5) );
point b = point(cubeSize / 2.0, cubeSize / 2.0, -(cubeSize *0.5) );
point c = point(cubeSize / 2.0, -cubeSize / 2.0, -(cubeSize *0.5));
point d = point(-cubeSize / 2.0, -cubeSize / 2.0, -(cubeSize *0.5));

square* firstSquare = new square(a, b, c, d);

cube* firstCube = new cube(firstSquare, "FCC");

//rubik* myRubik = new rubik(firstCube);

rubik* firstRubik = new rubik(firstCube);
SuperRubik* myRubik = new SuperRubik(firstRubik);
bool flag = true;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	int angulo = 30;
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		
		if (key == GLFW_KEY_F && flag) {
			flag = false;
			myRubik->rotate('F');
			flag = true;
		}
		if (key == GLFW_KEY_B && flag) {
			flag = false;
			myRubik->rotate('B');
			flag = true;
		}
		
		if (key == GLFW_KEY_L && flag) {
			flag = false;
			myRubik->rotate('L');
			flag = true;
		}
		if (key == GLFW_KEY_R && flag) {
			flag = false;
			myRubik->rotate('R');
			flag = true;
		}
		if (key == GLFW_KEY_U && flag) {
			flag = false;
			myRubik->rotate('U');
			flag = true;
		}
		if (key == GLFW_KEY_D && flag) {
			flag = false;
			myRubik->rotate('D');
			flag = true;
		}
		if (key == GLFW_KEY_S && flag) {
			flag = false;
			string moves = myRubik->moves;
			string solution;
			solution = rubikS::solve(moves);
			myRubik->solver(solution);
			flag = true;
		}

		if (key == GLFW_KEY_X && flag) {
			flag = false;
			myRubik->disorder(1);
			flag = true;
		}
		/*if (key == GLFW_KEY_Z && flag) {
			flag = false;
			myRubik->disorder(5);
			flag = true;
		}*/


		//ROTACION 
		angulo = 45;
		if (key == GLFW_KEY_LEFT){
			myRubik->rotateY(angulo);
			anguloY += angulo;
		}
		if (key == GLFW_KEY_RIGHT)
		{
			myRubik->rotateY(-angulo);
			anguloY -= angulo;
		}

		if (key == GLFW_KEY_UP)
		{
			myRubik->rotateX(angulo);
			anguloX += angulo;
		}
		if (key == GLFW_KEY_DOWN)
		{
			myRubik->rotateX(-angulo);
			anguloX -= angulo;
		}

		//VELOCITY
		if (key == GLFW_KEY_KP_ADD){
			myRubik->setVelocity(-1); // menor numero más rápido
		}
		if (key == GLFW_KEY_KP_SUBTRACT) {
			myRubik->setVelocity(1); //mayor numero más lento
		}
	}
}

void drawRubik();

int main()
{
	cout << "\t\t\t" << "Computacion Grafica [CG-2021-I]" << endl << endl;
	cout << "INTEGRANTES:" << endl << endl;
	cout << "- Armando Miguel Zegarra Castillo" << endl;
	cout << "- Mariangela Pacheco Delgado" << endl << endl << endl;

	cout << "INSTRUCCIONES:" << endl << endl;
	cout << "-PARA GIRAR TODO EL CUBO PRESIONE LAS FLECHAS" << endl;
	cout << "-PARA ROTAR CAPA POR CAPA PRESIONE F,B,L,R,U,D" << endl;;
	cout << "-PARA RESOLVER EL CUBO PRESIONE S" << endl;
	cout << "-PARA AUMENTAR O REDUCIR LA VELOCIDAD DEL CUBO PRESIONA + o -" << endl;
	generateColors(numColors);

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	compileShader();

	myRubik->setVertex();
	while (!glfwWindowShouldClose(window))
	{				
		myRubik->draw();
		bufferArray();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void drawRubik()
{
	int numCubes = vertex.size()/3;
	for (int i =0* 24; i < numCubes * 24; i += 24)
	{
		//FRONT
		SP = vSP[5];//Anaranjado
		glUseProgram(SP);
		glDrawArrays(GL_TRIANGLE_FAN, i, 4);

		SP = vSP[6]; glUseProgram(SP); //Negro
		glDrawArrays(GL_LINE_LOOP, i, 4);


		//BACK
		SP = vSP[1];//Rojo
		glUseProgram(SP);
		glDrawArrays(GL_TRIANGLE_FAN, i + 4, 4);

		SP = vSP[6]; glUseProgram(SP); //Negro
		glDrawArrays(GL_LINE_LOOP, i + 4, 4);

		//LEFT
		SP = vSP[2];//Verde
		glUseProgram(SP);
		glDrawArrays(GL_TRIANGLE_FAN, i + 8, 4);
		SP = vSP[6]; glUseProgram(SP); //Negro
		glDrawArrays(GL_LINE_LOOP, i + 8, 4);

		//RIGHT
		SP = vSP[3]; //Azul
		glUseProgram(SP);
		glDrawArrays(GL_TRIANGLE_FAN, i + 12, 4);
		SP = vSP[6]; glUseProgram(SP); //Negro
		glDrawArrays(GL_LINE_LOOP, i + 12, 4);

		//TOP
		SP = vSP[0]; //Blanco
		glUseProgram(SP);
		glDrawArrays(GL_TRIANGLE_FAN, i + 16, 4);
		SP = vSP[6]; glUseProgram(SP); //Negro
		glDrawArrays(GL_LINE_LOOP, i + 16, 4);


		//DOWN
		SP = vSP[4]; //Amarillo
		glUseProgram(SP);
		glDrawArrays(GL_TRIANGLE_FAN, i + 20, 4);
		SP = vSP[6]; glUseProgram(SP); //Negro
		glDrawArrays(GL_LINE_LOOP, i + 20, 4);

	}
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

