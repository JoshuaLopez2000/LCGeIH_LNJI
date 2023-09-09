/*---------------------------------------------------------*/
/* ----------------   Práctica 3 --------------------------*/
/*-----------------    2024-1   ---------------------------*/
/*-------Alumno: López Nava Joshua Ivan		 --------------*/
/*-------Cuenta: 317309733               ------------------*/
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO[2], VAO[2], EBO[2]; // creación de contenedores para posteriormente pasar los arreglos a memoria de video Vertex Budget Objet
// Se crean los tres para cada arreglo
//[2] (se están creando dos de cada uno

void myData(void);
void getResolution(void);

//For Keyboard
//Condiciones iniciales de objetos en pantalla
float	movX = -5,
		movY = 5,
		movZ = -30;

float	rotY = 0;


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{	

	GLfloat verticesCubo[] = {
		//Position				//Color
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0 - Frontal
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V1
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V4
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5

		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	//V3
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V6
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7

		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4 - Izq
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	//V7
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V0

		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5 - Der
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V1
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V6
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2

		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4 - Sup
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V5
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V7
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6

		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0 - Inf
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	//V3
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V1
	};

	GLfloat verticesLuis[] = {
		// positions			//Color
		-0.5f, 0.7f, -0.5f,		1.0f, 0.0f, 0.0f,	//V0
		0.5f, 0.7f, -0.5f,		1.0f, 0.0f, 1.0f,	//V1
		0.5f, 0.3f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		-0.2f, 0.3f, -0.5f,		1.0f, 1.0f, 0.0f,	//V3
		-0.2f, -0.3f, -0.5f,	0.0f, 1.0f, 0.0f,	//V4
		0.5f, -0.3f, -0.5f,		0.0f, 1.0f, 1.0f,	//V5
		0.5f, -0.7f, -0.5f,		0.0f, 0.0f, 1.0f,	//V6
		-0.5f, -0.7f, -0.5f,	1.0f, 1.0f, 1.0f,	//V7
	};

	unsigned int indicesLuis[] =
	{
		3, 2, 1, 0, 7, 4,
		7, 4, 5, 6
	};

	glGenVertexArrays(2, VAO); // dos contenerdores VAO 
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);	//Only if we are going to work with index


	glBindVertexArray(VAO[0]); // Se dice cual utilizár
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCubo), verticesCubo, GL_STATIC_DRAW); //se vacía la información que tienen los vertices

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glBindVertexArray(VAO[1]); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLuis), verticesLuis, GL_STATIC_DRAW); //en el contenedor 1 se vacia el contenedor de vertices Luis

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesLuis), indicesLuis, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void printEmj(float color[], int figura[], int tam, glm::mat4 modelOp, Shader myShader) {

	int	i = 0;
	float	x = 0.0f,
			y = 0.0f;
	for (i = 0; i <= tam; i++) {
		switch (figura[i]) {
		case 0:
			x += 1.0f;
			break;
		case 1:
			//aqui se genera el cubo actaul y se aumenta una posición a la derecha
			modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f)); // Si se quisieran agregar más figuras entonces se tiene que afectar X como parametro (case: -1, x = inicio)
			myShader.setMat4("model", modelOp);
			myShader.setVec3("aColor", glm::vec3(color[0],color[1],color[2]));
			glDrawArrays(GL_TRIANGLES, 0, 36);
			x += 1;
			break;
		case -1:
			x = 0.0f;
			y -= 1.0f;
			break;
		default:
			return;
			break;
		}
	}
}

int main()
{
	float colorRGB[] = { 0, 0, 0, };
	int emj0[] = {
		0,0,0,0,1,1,1,-1,
		0,0,0,0,0,1,1,1,-1,
		0,0,0,0,1,1,1,1,1,-1,
		0,0,0,0,1,1,1,1,1,-1,
		0,0,0,1,1,1,1,1,1,1,1,-1,
		0,0,1,0,0,0,1,0,0,0,1,-1,
		0,0,1,0,0,0,1,0,0,0,1,-1,
		0,0,1,0,0,0,1,0,0,0,1,-1,
		0,1,1,0,0,0,1,0,0,0,1,1,-1,
		0,1,1,1,1,1,1,1,1,1,1,1,-1,
		1,1,1,1,0,0,0,0,0,1,1,1,1,-1,
		1,1,1,1,1,0,0,0,1,1,1,1,1,-1,
		0,1,1,1,1,1,1,1,1,1,1,1,0,-1,
	};
	int tam_emoji0 = sizeof(emj0) / sizeof(emj0[0]);

	int ojosBoca_emj0[] = {
		-1,
		-1,
		-1,
		-1,
		-1,
		0,0,0,1,1,1,0,1,1,1,-1,
		0,0,0,1,0,1,0,1,0,1,-1,
		0,0,0,1,0,1,0,1,0,1,-1,
		0,0,0,1,1,1,0,1,1,1,-1,
		-1,
		0,0,0,0,1,1,1,1,1,-1,
		0,0,0,0,0,1,1,1,0,-1,
	};
	int tamOjos_emj0 = sizeof(ojosBoca_emj0) / sizeof(ojosBoca_emj0[0]);

	int pupilas_emj0[] = {
		-1,
		-1,
		-1,
		-1,
		-1,
		-1,
		0,0,0,0,1,0,0,0,1,-1,
		0,0,0,0,1,0,0,0,1,
	};
	int tamPupilas_emj0 = sizeof(pupilas_emj0) / sizeof(pupilas_emj0[0]);

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 3 20241", NULL, NULL);
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


	//Mis funciones
	//Datos a utilizar
	myData();
	glEnable(GL_DEPTH_TEST);

	//Prepare to draw the scene with Projections
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	Shader myShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	myShader.use();
	// create transformations and Projection
	glm::mat4 modelOp = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 viewOp = glm::mat4(1.0f);			//Use this matrix for ALL models
	glm::mat4 projectionOp = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" in order to change how we see the information
	projectionOp = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	//projectionOp = glm::ortho(-5.0f, 5.0f, -3.0f, 3.0f, 0.1f, 10.0f);

    // render loop
    // While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		my_input(window);

		// render
		// Backgound color
		glClearColor(0.619f, 0.619f, 0.619f, 1.0f); // Cambiar color de fondo (3 primeros)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		/*******************************************/
		//Use "view" in order to affect all models
		viewOp = glm::translate(glm::mat4(1.0f), glm::vec3(movX, movY, movZ)); // aplicar translación a la matriz de vista, vec3: cuanto se va a mover sobre el eje x,y,z
		viewOp = glm::rotate(viewOp, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
		// pass them to the shaders
		myShader.setMat4("model", modelOp);
		myShader.setMat4("view", viewOp);
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		myShader.setMat4("projection", projectionOp);


		glBindVertexArray(VAO[1]);	//Enable data array [1] | Se indica con que contenedor se va a trabajar (letra C en este caso)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]); //Only if we are going to work with index

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); //
		myShader.setMat4("model", modelOp);
		//glDrawArrays(GL_LINE_LOOP, 0, 8); //My C | LETRA C
		//glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(float)));	//to Draw using index
		//glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(6 * sizeof(float)));	//to Draw using index


		/*-------------------Second figure-------------------*/
		glBindVertexArray(VAO[0]);//Enable data array [0] | Contenedor 0 son los vertices que referencían al cubo

		//Sección que dibuja el "cuerpo" del primer emoji
		colorRGB[0] = 0.47f; colorRGB[1] = 0.2f; colorRGB[2] = 0.0f;
		printEmj(colorRGB, emj0, tam_emoji0, modelOp, myShader);

		//Dibujado del ojos y boca del primer emoji 
		colorRGB[0] = 1.0f; colorRGB[1] = 1.0f; colorRGB[2] = 1.0f;
		printEmj(colorRGB, ojosBoca_emj0, tamOjos_emj0, modelOp, myShader);

		//Dibujando pupilas
		colorRGB[0] = 0.0f; colorRGB[1] = 0.0f; colorRGB[2] = 0.0f;
		printEmj(colorRGB, pupilas_emj0, tamPupilas_emj0, modelOp, myShader);
		glBindVertexArray(0);
		/*****************************************************************/
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
void my_input(GLFWwindow *window) // procesar llamadas del teclado para realizar acciones
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);


	//Matriz de vista affecta a todo el escenario
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.1f;

	//rotación
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 2.1f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 2.1f;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}