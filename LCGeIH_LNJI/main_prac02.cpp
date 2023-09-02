/*---------------------------------------------------------*/
/* ----------------   Práctica 2 --------------------------*/
/*-----------------    2024-1   ---------------------------*/
/*------------- López Nava Joshua Ivan ---------------*/
#include <glew.h>
#include <glfw3.h>
#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

GLFWmonitor *monitors;
GLuint VBO[2], VAO[2], EBO[2];
GLuint shaderProgramYellow, shaderProgramColor;

static const char* myVertexShader = "										\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
																			\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);						\n\
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
static const char* myFragmentShaderYellow = "								\n\
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
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{
	float vertices[] = 
	{

		/*
		* Color solido
		// positions					//Color (colores divididos entre 255 en el caso de rgb)
		-0.55862f, 0.7174f, 0.0f,		0.6f, 0.2f, 0.0f,//V0
		-0.58852f, 0.43018f, 0.0f,		0.6f, 0.2f, 0.0f,//V1
		-0.34188f, 0.48464f, 0.0f,		0.6f, 0.2f, 0.0f,//V2
		-0.53407f, 0.25401f, 0.0f,		0.6f, 0.2f, 0.0f,//V3
		-0.63155f, 0.88366f, 0.0f,		0.6f, 0.2f, 0.0f,//V4
		-0.17576f, 0.48502f, 0.0f,		0.6f, 0.2f, 0.0f,//V5
		-0.00013f, 0.48084f, 0.0f,		0.6f, 0.2f, 0.0f,//V6
		-0.67549f, 0.41392f, 0.0f,		0.6f, 0.2f, 0.0f,//V7
		-0.69495f, 0.07749f, 0.0f,		0.6f, 0.2f, 0.0f,//v8
		-0.0f, 0.2f, 0.0f,				0.6f, 0.2f, 0.0f,//V9
		-0.25594f, 0.07264f, 0.0f,		0.6f, 0.2f, 0.0f,//V10
		-0.19742f,-0.12982f, 0.0f,		0.6f, 0.2f, 0.0f,//V11
		-0.4f ,-0.1f , 0.0f,			0.6f, 0.2f, 0.0f,//V12
		*/
		
		// positions					//Color (colores divididos entre 255 en el caso de rgb)
		//Mitad Izquierda
		-0.55862f, 0.7174f, 0.0f,		0.2f, 0.0f, 0.2f,//V0x
		-0.58852f, 0.43018f, 0.0f,		0.6f, 0.2f, 0.4f,//V1x
		-0.34188f, 0.48464f, 0.0f,		0.2f, 0.0f, 0.2f,//V2x
		-0.53407f, 0.25401f, 0.0f,		0.4f, 0.0f, 0.0f,//V3x
		-0.63155f, 0.88366f, 0.0f,		0.2f, 0.0f, 0.2f,//V4x
		-0.17576f, 0.48502f, 0.0f,		0.2f, 0.0f, 0.2f,//V5x
		-0.00013f, 0.48084f, 0.0f,		0.8f, 0.0f, 0.6f,//V6x
		-0.67549f, 0.41392f, 0.0f,		0.6f, 0.2f, 0.4f,//V7x
		-0.69495f, 0.07749f, 0.0f,		0.4f, 0.0f, 0.0f,//V8x
		-0.0f, 0.2f, 0.0f,				0.8f, 0.0f, 0.6f,//V9x
		-0.25594f, 0.07264f, 0.0f,		0.8f, 0.0f, 0.6f,//V10x
		-0.19742f,-0.12982f, 0.0f,		0.8f, 0.0f, 0.4f,//V11x
		-0.4f ,-0.1f , 0.0f,			0.8f, 0.0f, 0.4f,//V12x
		-0.80166f, -0.3381f, 0.0f,		0.4f, 0.0f, 0.788f,//V13
		-0.55174f, -0.54138f, 0.0f,		0.8f, 0.0f, 0.6f,//V14
		-0.309f ,-0.24244f , 0.0f,		0.8f, 0.0f, 0.6f,//V15
		-0.15794f, -0.26231f, 0.0f,		0.8f, 0.0f, 0.8f,//V16
		-0.29387f, -0.72933f, 0.0f,		0.8f, 0.0f, 0.8f,//V17

		//Mitad Derecha
		-0.55862f * -1, 0.7174f, 0.0f,		0.2f, 0.0f, 0.2f,//V18
		-0.58852f * -1, 0.43018f, 0.0f,		0.6f, 0.2f, 0.4f,//V19
		-0.34188f * -1, 0.48464f, 0.0f,		0.2f, 0.0f, 0.2f,//V20
		-0.53407f * -1, 0.25401f, 0.0f,		0.4f, 0.0f, 0.0f,//V21
		-0.63155f * -1, 0.88366f, 0.0f,		0.2f, 0.0f, 0.2f,//V22
		-0.17576f * -1, 0.48502f, 0.0f,		0.2f, 0.0f, 0.2f,//V23
		-0.00013f * -1, 0.48084f, 0.0f,		0.8f, 0.0f, 0.6f,//V24
		-0.67549f * -1, 0.41392f, 0.0f,		0.6f, 0.2f, 0.4f,//V25
		-0.69495f * -1, 0.07749f, 0.0f,		0.4f, 0.0f, 0.0f,//V26
		-0.0f * -1, 0.2f, 0.0f,				0.8f, 0.0f, 0.6f,//V27
		-0.25594f * -1, 0.07264f, 0.0f,		0.8f, 0.0f, 0.6f,//V28
		-0.19742f * -1,-0.12982f, 0.0f,		0.8f, 0.0f, 0.4f,//V29
		-0.4f * -1,-0.1f , 0.0f,			0.8f, 0.0f, 0.4f,//V30
		-0.80166f * -1, -0.3381f, 0.0f,		0.4f, 0.0f, 0.788f,//V31
		-0.55174f * -1, -0.54138f, 0.0f,	0.8f, 0.0f, 0.6f,//V32
		-0.309f * -1,-0.24244f , 0.0f,		0.8f, 0.0f, 0.6f,//V33
		-0.15794f * -1, -0.26231f, 0.0f,	0.8f, 0.0f, 0.8f,//V34
		-0.29387f * -1, -0.72933f, 0.0f,	0.8f, 0.0f, 0.8f,//V35

		//Nariz - boca
		-0.11313f ,-0.68494f , 0.0f,		0.8f, 0.0f, 0.6f,//V36
		0.11917f ,-0.68647f , 0.0f,			0.8f, 0.0f, 0.6f,//V37

		0.14414f, -0.79295f, 0.0f,			0.8f, 0.0f, 0.6f,//V38
		0.0f, -0.840f, 0.0f,				0.4f, 0.0f, 0.2f,//V39x
		-0.14013f, -0.79549f, 0.0f,			0.8f, 0.0f, 0.6f,//V40
		-0.23438f, -0.88974f, 0.0f,			0.4f, 0.0f, 0.2f,//V41x
		-0.0f, -0.969f, 0.0f,				0.4f, 0.0f, 0.2f,//V42x
		0.23481f, -0.88953f, 0.0f,			0.4f, 0.0f, 0.2f,//V43x


		//Vertices con colores de oreja izquierda
		-0.55862f, 0.7174f, 0.0f,		1.0f, 0.6f, 0.8f,//V44
		-0.58852f, 0.43018f, 0.0f,		1.0f, 0.6f, 0.8f,//V45
		-0.34188f, 0.48464f, 0.0f,		1.0f, 0.6f, 0.8f,//V46
		-0.53407f, 0.25401f, 0.0f,		1.0f, 0.6f, 0.8f,//V47

		//Oreja Derecha
		0.55862f, 0.7174f, 0.0f,		1.0f, 0.6f, 0.8f,//V48
		0.58852f, 0.43018f, 0.0f,		1.0f, 0.6f, 0.8f,//V49
		0.34188f, 0.48464f, 0.0f,		1.0f, 0.6f, 0.8f,//V50
		0.53407f, 0.25401f, 0.0f,		1.0f, 0.6f, 0.8f,//V51

		//Ojo L 53, 52, 55, 54
		-0.19742f,-0.12982f, 0.0f,		1.0f, 1.0f, 1.0f,//V52 (11)
		-0.4f ,-0.1f , 0.0f,			1.0f, 1.0f, 1.0f,//V53 (12)
		-0.309f ,-0.24244f , 0.0f,		1.0f, 1.0f, 1.0f,//V54 (15)
		-0.15794f, -0.26231f, 0.0f,		1.0f, 1.0f, 1.0f,//V55 (16)

		//Ojo R 57, 56, 59, 58
		0.19742f,-0.12982f, 0.0f,		1.0f, 1.0f, 1.0f,//V56 
		0.4f ,-0.1f , 0.0f,				1.0f, 1.0f, 1.0f,//V57
		0.309f ,-0.24244f , 0.0f,		1.0f, 1.0f, 1.0f,//V58
		0.15794f, -0.26231f, 0.0f,		1.0f, 1.0f, 1.0f,//V59

		// Nariz (color) 63, 64, 60, 61, 62
		-0.11313f ,-0.68494f , 0.0f,		0.0f, 0.0f, 0.0f,//V60 36
		0.11917f ,-0.68647f , 0.0f,			0.0f, 0.0f, 0.0f,//V61 37
		0.14414f, -0.79295f, 0.0f,			0.0f, 0.0f, 0.0f,//V62 38
		0.0f, -0.840f, 0.0f,				0.0f, 0.0f, 0.0f,//V63 39
		-0.14013f, -0.79549f, 0.0f,			0.0f, 0.0f, 0.0f,//V64 40
	};

	unsigned int indices[] =
	{
		/*
		2, 4, 0, 1, 3, // usando triangle fan con 3 como pivote
		5, 6, 3, 2, 4,
		1, 0, 4, 7, 8, 3,
		3, 6, 9, 10, 11, 12, 8,
		*/

		/*
		Colores solidos
		2, 0, 4, 5, 3,
		1, 0, 4, 7, 8, 3,
		3, 5, 6, 9, 10, 11, 12, 8,
		*/
		
		//Mitad Izquierda
		4, 7, 1, 0, 2, 5,
		8, 7, 1, 3, 10, 11, 12, 13,
		6, 2, 3, 10, 9,
		13, 8, 12, 15, 14,
		17, 14, 15, 16, 36, 40,

		//Mitad Derecha
		4 + 18, 7 + 18, 1 + 18, 0 + 18, 2 + 18, 5 + 18,
		8 + 18, 7 + 18, 1 + 18, 3 + 18, 10 + 18, 11 + 18, 12 + 18, 13 + 18,
		6 + 18, 2 + 18, 3 + 18, 10 + 18, 9 + 18,
		13 + 18, 8 + 18, 12 + 18, 15 + 18, 14 + 18,
		17 + 18, 14 + 18, 15 + 18, 16 + 18, 37, 38,

		//Frente
		34, 28, 9, 10, 16, 36, 37,
		39, 17, 41, 42, 43, 35, //39 pivote

		//Oreja L
		45, 44, 46, 47,
		//Oreja R
		49, 48, 50, 51,

		//Ojo L
		53, 52, 55, 54,
		//Ojo R
		57, 56, 59, 58,

		//Nariz 
		63, 64, 60, 61, 62,

	};

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);



	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // funcion encargada de unir el arreglo de datos con el shader
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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


	//Crear el Programa que combina Geometría con Color
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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 2",NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
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
		glUseProgram(shaderProgramColor);

		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);

		glPointSize(10.0);
		//-----------------------------------------------------------------------------------------------------------
		/*Color Solido
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(0 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(5 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, (void*)(11 * sizeof(float)));
		*/

		
		//Mitad Izquierda
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, (void*)(6 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(14 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(19 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(float)));

		
		//Mitad Derecha
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(30 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, (void*)(36 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(44 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(49 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(54 * sizeof(float)));
		
		//glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

		//Frente
		glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_INT, (void*)(60 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(67 * sizeof(float)));

		//Orejas
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(73 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(77 * sizeof(float)));

		//Ojos
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(81 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(85 * sizeof(float)));

		//Nariz
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(89 * sizeof(float)));


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
    //glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);  //Close
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}