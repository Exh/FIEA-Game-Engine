/**	@file OpenGL.cpp
*	Contains implementation for WinMain
*/
#include "pch.h"

/**	Windows Application Program entry point
*	@param instance : handle to this window
*	@param previousInstance : not used always null
*	@param commandLine : command line arguments
*	@param showCommand : options for displaying window
*/
int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	const glm::vec4 CornflowerBlue = glm::vec4(0.392f, 0.584f, 0.929f, 1.0f); //Window background color

	//Init the GLFW loading library
	if (!glfwInit())
	{
		return -1;
	}

	//Creating a 800x600 window with title and returning handle to it
	GLFWwindow* window = glfwCreateWindow(800, 600, "FIEA Game Engine - OpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		return -1;
	}

	glfwMakeContextCurrent(window);

	//setup OpenGL
	if (gl3wInit() != 0)
	{
		return -1;
	}

	//set where on screen we want to render
	glViewport(0, 0, 800, 600);

	//do until for window is closed
	while (!glfwWindowShouldClose(window))
	{
		//clear color buffer
		glClearBufferfv(GL_COLOR, 0, &CornflowerBlue[0]);

		//swap front and back buffers (double buffering)
		glfwSwapBuffers(window);

		//check for keyboard or mouse input
		glfwPollEvents();
	}

	//clean up
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}