#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW which version we are using - OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile - only modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW window
	GLFWwindow* window = glfwCreateWindow(800, 800, "Softbody Simulation", NULL, NULL);
	// Error check in case window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Add window to current context
	glfwMakeContextCurrent(window);

	// Load glad to configure OpenGL
	gladLoadGL();

	// Specify viewport of OpenGL in the window
	// From x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// Specify background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean back buffer and assign color
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap front and back buffers
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Handle all GLFW events
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}