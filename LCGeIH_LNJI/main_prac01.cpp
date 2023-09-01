/*---------------------------------------------------------*/
/* ----------------   Pr�ctica 1 --------------------------*/
/*-----------------    2024-1   ---------------------------*/
/*------------- (L�pez Nava Joshua Ivan) ---------------*/
#include <glew.h>
#include <glfw3.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow* window);

// settings
// Window size
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

GLFWmonitor* monitors;
GLuint VBO[2], VAO[2], EBO[2];
GLuint shaderProgramYellow, shaderProgramColor;

static const char* myVertexShader = "										\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
																			\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);							\n\
}";

static const char* myVertexShaderColor = "									\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
layout (location = 1) in vec3 aColor;										\n\
out vec3 ourColor;															\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos, 1.0);											\n\
	ourColor = aColor;														\n\
}";

// Fragment Shader
static const char* myFragmentShaderYellow = "									\n\
#version 330																\n\
																			\n\
out vec3 finalColor;														\n\
																			\n\
void main()																	\n\
{																			\n\
    finalColor = vec3(1.0f, 1.0f, 0.0f);									\n\
}";

static const char* myFragmentShaderColor = "								\n\
#version 330 core															\n\
out vec4 FragColor;															\n\
in vec3 ourColor;															\n\
																			\n\
void main()																	\n\
{																			\n\
	FragColor = vec4(ourColor, 1.0f);										\n\
}";

void myData(void);
void setupShaders(void);
void display(void);
void getResolution(void);


void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{
	float vertices[] =
	{/*
	 // positions    x,y,z	//
		0.0f,	0.0f,	0.0f,	//0
		0.8f,	0.78f,	0.0f,	//1
		-0.8f,	0.89f,	0.0f,	//2
		-0.8f,	-0.75f,	0.0f,	//3
		0.7f,	-0.8f,	0.0f,	//4
		0.94f,	-0.6f,	0.0f,	//5
	*/

		-0.2f,	-0.8f,	0.0f,	//0
		-0.5f,	-0.8f,	0.0f,	//1
		-0.5f,	0.8f,	0.0f,	//2
		0.7f,	0.8f,	0.0f,	//3
		0.7f,	0.5f,	0.0f,	//4
		-0.2f,	0.5f,	0.0f,	//5	
		-0.2f,	0.0f,	0.0f,	//6
		0.2f,	0.0f,	0.0f,	//7
		0.2f,	-0.2f,	0.0f,	//8
		-0.2f,	-0.2f,	0.0f,	//9

	};

	unsigned int indices[] =
	{
		5, 4, 3,
		2, 3, 5,
		1, 9, 0,
		6, 7, 8,
		6, 8, 9,
		2, 5, 6,
		2, 6, 1,
		1, 9, 0,
		1, 9, 6
	};

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);



	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void setupShaders()
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &myVertexShader, NULL);
	glCompileShader(vertexShader);

	unsigned int vertexShaderColor = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderColor, 1, &myVertexShaderColor, NULL);
	glCompileShader(vertexShaderColor);

	unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &myFragmentShaderYellow, NULL);
	glCompileShader(fragmentShaderYellow);

	unsigned int fragmentShaderColor = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderColor, 1, &myFragmentShaderColor, NULL);
	glCompileShader(fragmentShaderColor);


	//Crear el Programa que combina Geometr�a con Color
	shaderProgramYellow = glCreateProgram();
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	shaderProgramColor = glCreateProgram();
	glAttachShader(shaderProgramColor, vertexShaderColor);
	glAttachShader(shaderProgramColor, fragmentShaderColor);
	glLinkProgram(shaderProgramColor);
	//Check for errors 

	//ya con el Programa, el Shader no es necesario
	glDeleteShader(vertexShader);
	glDeleteShader(vertexShaderColor);
	glDeleteShader(fragmentShaderYellow);
	glDeleteShader(fragmentShaderColor);

}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 1_LNJI", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30); //configuraci�n de la posici�n de la ventana
	glfwMakeContextCurrent(window);	//funci�n que despliega la ventana una vez terminada la configuraci�n
	glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//My Functions
	//Setup Data to use
	myData();
	//To Setup Shaders
	setupShaders();

	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		my_input(window);

		// render
		// Background color
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Display Section
		glUseProgram(shaderProgramYellow);

		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);

		glPointSize(10.0);

		/*
		//glDrawElements(GL_POINTS, 5, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_LINES, 0, 6); //GL_POINTS O GL_LINES para lineas 
		// primer parametro es el inicio, segundo cuantos elementos tomar a partir del inicio
		//glDrawArrays(GL_POINTS, 4, 1);
		//glDrawArrays(GL_LINE_STRIP, 0, 6); //Genera segmentos de linea uno detr�s de otro, no es necesario que sean pares
		//-----------------------------------------------
		//Comando GL_LINE_LOOP genera una figura cerrada uniendo el ultimo elemento con el primero
		//glDrawArrays(GL_LINE_LOOP, 0, 6);
		//---------------------------------
		//GL_TRIANGLES_GENERA TRIANGULOS TOMANDO EN CUENTA UN NUMERO MULTIPLO DE 3, POR CADA MULTIPLO GENERA UN TRIANGULO
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); //Genera un triangulo para cada uno de los elementos hasta n-2, tomando los dos elementos siguientes 
		//glDrawArrays(GL_TRIANGLE_FAN, 0, 6); //toma al elemento inicial como referencia para generar todos los triangulos posibles, todas las combinaciones que se puedan generar con el elemento inicial
		*/

		glDrawArrays(GL_LINE_LOOP, 0, 10); // Loop ya que es una figura cerrada
		//glDrawArrays(GL_TRIANGLES, 3, 3); // Para formar el triangulo 5-4-3

		glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0); // Va a tomar el arreglo adicional creado (idices), se indica primero la cantidad y luego el inicio
		// necesario aumentar el tama�o de elementos, evita duplicar vertices

		glBindVertexArray(0);
		glUseProgram(0);

		//End of Display Section

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);  //Close
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}