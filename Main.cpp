#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex shader source
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
// Fragment shader source
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW which version we are using - OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile - only modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right
		0.0f, 0.5f * float(sqrt(3)) / 3 , 0.0f // Upper
	};

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

	// Create vertex shader object reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach vertex shader source to vertex object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile vertex shader into machine code
	glCompileShader(vertexShader);

	// Create fragment shader object reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach fragment shader source to fragment object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile fragment shader into machine code
	glCompileShader(fragmentShader);

	// Create shader program object reference
	GLuint shaderProgram = glCreateProgram();
	// Attach vertex and fragment shaders to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Link shaders together into program
	glLinkProgram(shaderProgram);

	// Delete shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create reference objects for vertex array and buffer objects
	GLuint VAO, VBO;

	// Generate VAO and VBO with 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make VAO current vertex object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce vertices into VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure vertex attribute so OpenGL can read VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable vertex attribute so OpenGL can use it
	glEnableVertexAttribArray(0);

	// Bind VAO and VBO to 0 to prevent accidental modification
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Specify background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean back buffer and assign color
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap front and back buffers
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell openGL which shader program to use
		glUseProgram(shaderProgram);
		// Bind VAO so OpenGL can use it
		glBindVertexArray(VAO);
		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		// Handle all GLFW events
		glfwPollEvents();
	}

	// Delete all created objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}