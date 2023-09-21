/*---------------------------------------------------------*/
/* ----------------   Práctica 4 --------------------------*/
/*-----------------    2024-1   ---------------------------*/
/*-------------Alumno:López Nava Joshua Ivan---------------*/
/*------------- No. de cuenta: 317309733    ---------------*/
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
GLuint VBO, VAO, EBO;

void myData(void);
void getResolution(void);

//For Keyboard
float	movX = -10.0f,
		movY = 0.0f,
		movZ = -30.0f;

float	rotX = 0.0f,
		rotY = 0.0f,
		rotZ = 0.0f;

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
		-0.5f, -0.5f, 0.5f,		//V0 - Frontal
		0.5f, -0.5f, 0.5f,		//V1
		0.5f, 0.5f, 0.5f,		//V5
		-0.5f, -0.5f, 0.5f,		//V0
		-0.5f, 0.5f, 0.5f,		//V4
		0.5f, 0.5f, 0.5f,		//V5

		0.5f, -0.5f, -0.5f,		//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	//V3
		-0.5f, 0.5f, -0.5f,		//V7
		0.5f, -0.5f, -0.5f,		//V2
		0.5f, 0.5f, -0.5f,		//V6
		-0.5f, 0.5f, -0.5f,		//V7

		-0.5f, 0.5f, 0.5f,		//V4 - Izq
		-0.5f, 0.5f, -0.5f,		//V7
		-0.5f, -0.5f, -0.5f,	//V3
		-0.5f, -0.5f, -0.5f,	//V3
		-0.5f, 0.5f, 0.5f,		//V4
		-0.5f, -0.5f, 0.5f,		//V0

		0.5f, 0.5f, 0.5f,		//V5 - Der
		0.5f, -0.5f, 0.5f,		//V1
		0.5f, -0.5f, -0.5f,		//V2
		0.5f, 0.5f, 0.5f,		//V5
		0.5f, 0.5f, -0.5f,		//V6
		0.5f, -0.5f, -0.5f,		//V2

		-0.5f, 0.5f, 0.5f,		//V4 - Sup
		0.5f, 0.5f, 0.5f,		//V5
		0.5f, 0.5f, -0.5f,		//V6
		-0.5f, 0.5f, 0.5f,		//V4
		-0.5f, 0.5f, -0.5f,		//V7
		0.5f, 0.5f, -0.5f,		//V6

		-0.5f, -0.5f, 0.5f,		//V0 - Inf
		-0.5f, -0.5f, -0.5f,	//V3
		0.5f, -0.5f, -0.5f,		//V2
		-0.5f, -0.5f, 0.5f,		//V0
		0.5f, -0.5f, -0.5f,		//V2
		0.5f, -0.5f, 0.5f,		//V1
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCubo), verticesCubo, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 4 2024-1", NULL, NULL);
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

	Shader myShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");
	myShader.use();

	glm::mat4 viewOp = glm::mat4(1.0f);			//Use this matrix for ALL models
	glm::mat4 projectionOp = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" in order to change how we see the information
	projectionOp = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	glm::mat4 tempBrazo = glm::mat4(1.0f); //temporal (se pueden declarar más de uno
	glm::mat4 tempPollo = glm::mat4(1.0f);
	glm::mat4 tempPiernaL = glm::mat4(1.0f);
	glm::mat4 tempPiernaR = glm::mat4(1.0f);

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);

        // render
        // Background color
        glClearColor(178.0f/255.0f, 223.0f / 255.0f, 224.0f / 219.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi bloque de dibujo
		/*******************************************/
		glm::mat4 modelOp = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
		//Use "view" in order to affect all models
		viewOp = glm::translate(glm::mat4(1.0f), glm::vec3(movX, movY, movZ)); //toma de referencia el origen como primer argumento
		viewOp = glm::rotate(viewOp, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f)); //Toma de referencia la matriz de vista (lo que obtuvo de la operación anterior, se van concatenando)
		viewOp = glm::rotate(viewOp, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f)); 
		viewOp = glm::rotate(viewOp, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f)); //ultimo argumento son los ejes de rotación (en esta caso rota en el eje Z)
		// pass them to the shaders
		myShader.setMat4("model", modelOp);
		myShader.setMat4("view", viewOp);
		myShader.setMat4("projection", projectionOp);

		//Model
		glBindVertexArray(VAO);
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(4.0f, 5.0f, 1.0f)); //factores de escala = valor final/valor inicial, mayor a 1 crece, 1 permanece, 0-1 se reduce, 0 se elimina
		myShader.setMat4("model", modelOp); 
		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f)); //Amarillo
		glDrawArrays(GL_TRIANGLES, 0, 36);// cuerpo

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.5f+(0.5f/2.0f), 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.5f, 0.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //Cuello

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 4.25f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.5f, 2.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //Cabeza

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(4.0f, 1.0f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //Cadera

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.25f, -4.75f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.5f, 3.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //Pierna R

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-1.25f, -4.75f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.5f, 3.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //Pierna L

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(1.75f, -6.875f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f, 0.75f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //Pie R

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-1.75f, -6.875f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f, 0.75f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36); //Pie L

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f - (1.5f / 2.0f), (2.5f - (0.5f / 2.0f)), 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.5f, 0.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f)); //Amarillo
		glDrawArrays(GL_TRIANGLES, 0, 36); // ante brazo L

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f + (1.5f / 2.0f), (2.5f - (0.5f / 2.0f)), 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.5f, 0.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f)); //Amarillo
		glDrawArrays(GL_TRIANGLES, 0, 36); // ante brazo R

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f - (1.5f / 2.0f) - (1.5f / 2.0f) + (1.0f / 2.0f), (2.5f - (0.5f / 2.0f) - (3.5f / 2.0f)), 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f, 3.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f)); //Amarillo
		glDrawArrays(GL_TRIANGLES, 0, 36); // brazo L

		tempBrazo = modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f*(-2.0f - (1.5f / 2.0f) - (1.5f / 2.0f) + (1.0f / 2.0f)), (2.5f - (0.5f / 2.0f) - (3.5f / 2.0f)), 0.0f)); // se agrega la temporal para modelar la espada a partir de la mano/brazo
		modelOp = glm::scale(modelOp, glm::vec3(1.0f, 3.5f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f)); //Amarillo
		glDrawArrays(GL_TRIANGLES, 0, 36); // brazo R

		modelOp = glm::translate(tempBrazo, glm::vec3(0.0f, -(3.5f/2.0f)-(0.3f/2.0f ), 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f, 0.3f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(183.0f / 255.0f, 28.0f / 255.0f, 28.0f / 255.0f)); //Rojo oscuro
		glDrawArrays(GL_TRIANGLES, 0, 36); // mango Espada

		modelOp = glm::translate(tempBrazo, glm::vec3((1.0f / 2.0f) + (0.3f / 2.0f), -(3.5f / 2.0f) - (0.3f / 2.0f), 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.3f, 0.6f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(183.0f / 255.0f, 28.0f / 255.0f, 28.0f / 255.0f)); //Rojo oscuro
		glDrawArrays(GL_TRIANGLES, 0, 36); // Guarda Espada

		modelOp = glm::translate(tempBrazo, glm::vec3((1.0f / 2.0f) + (0.3f) + (3.5f / 2.0f), -(3.5f / 2.0f) - (0.3f / 2.0f), 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(3.5f, 0.3f, 1.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(189.0f / 255.0f, 189.0f / 255.0f, 189.0f / 255.0f)); // Gris
		glDrawArrays(GL_TRIANGLES, 0, 36); // Espada

		//////////////////////////////////////////////////////////////////////////////////////////////////

		// Figura Pollo

		tempPollo = modelOp = glm::translate(glm::mat4(1.0f), glm::vec3( 20.0f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f, 5.0f, 2.5f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(255.0f / 255.0f, 238.0f / 255.0f, 88.0f / 255.0f)); // Amarillo
		glDrawArrays(GL_TRIANGLES, 0, 36); // Cuerpo Pollo

		modelOp = glm::translate(tempPollo, glm::vec3((2.5f/2.0f)+((2.5f * 0.30f)/2.0f), -(2.5f / 4.0f), -(2.5f / 4.0f)));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f*0.30f, 5.0f*0.30f, 2.5f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(253.0f / 255.0f, 216.0f / 255.0f, 53.0f / 255.0f)); //Amarillo
		glDrawArrays(GL_TRIANGLES, 0, 36); // Ala Derecha

		modelOp = glm::translate(tempPollo, glm::vec3(-1.0f*((2.5f / 2.0f) + ((2.5f * 0.30f) / 2.0f)), -(2.5f / 4.0f), -(2.5f / 4.0f)));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f * 0.30f, 5.0f * 0.30f, 2.5f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(253.0f/255.0f,216.0f/255.0f,53.0f/255.0f)); //Amarillo
		glDrawArrays(GL_TRIANGLES, 0, 36); // Ala Izquierda

		modelOp = glm::translate(tempPollo, glm::vec3(0.0f, -(2.5f / 4.0f), (-2.5f / 2.0f) - (2.5f * 0.5/2.0f)));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f, 5.0f*0.30, 2.5f*0.5));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(255.0f / 255.0f, 238.0f / 255.0f, 88.0f / 255.0f)); //Amarillo
		glDrawArrays(GL_TRIANGLES, 0, 36); // Cola inf

		modelOp = glm::translate(tempPollo, glm::vec3(0.0f, (-(2.5f / 4.0f) + ((5.0*0.3f) / 2.0f)) + (5.0f * 0.10f) / 2, (-2.5f / 2.0f) - (2.5f * 0.5 / 2.0f)));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f*0.70f, 5.0f * 0.10f, 2.5f * 0.5));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(225.0f / 255.0f, 245.0f / 255.0f, 157.0f / 255.0f)); //Amarillo
		glDrawArrays(GL_TRIANGLES, 0, 36); // Cola sup

		tempPiernaR = modelOp = glm::translate(tempPollo, glm::vec3(2.5f/4.0f, -(5.0f / 2.0f) - (5.0f * 0.25f)/2.0f, (-2.5f / 2.0f) + (2.5f * 0.15f)/2.0f));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f*0.15f, 5.0f*0.25f , 2.5f*0.15f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(249.0f / 255.0f, 127.0f / 255.0f, 37.0f / 255.0f)); // Naranja
		glDrawArrays(GL_TRIANGLES, 0, 36); // Pierna R

		tempPiernaL = modelOp = glm::translate(tempPollo, glm::vec3(-1*(2.5f / 4.0f), -(5.0f / 2.0f) - (5.0f * 0.25f) / 2.0f, (-2.5f / 2.0f) + (2.5f * 0.15f) / 2.0f));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f * 0.15f, 5.0f * 0.25f, 2.5f * 0.15f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(249.0f / 255.0f, 127.0f / 255.0f, 37.0f / 255.0f)); // Naranja
		glDrawArrays(GL_TRIANGLES, 0, 36); // Pierna L

		modelOp = glm::translate(tempPiernaL, glm::vec3(0.0f, ((-5.0f * 0.25f) / 2.0f) - (0.25f / 2.0f), -((2.5f * 0.15f)/2) + (2.5f * 0.5f) / 2.0f));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f*0.4f, 0.25f, 2.5f*0.5f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(249.0f / 255.0f, 127.0f / 255.0f, 37.0f / 255.0f)); // Naranja
		glDrawArrays(GL_TRIANGLES, 0, 36); // Pata L

		modelOp = glm::translate(tempPiernaR, glm::vec3(-1.0f*0.0f, ((-5.0f * 0.25f) / 2.0f) - (0.25f / 2.0f), -((2.5f * 0.15f) / 2) + (2.5f * 0.5f) / 2.0f));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f * 0.4f, 0.25f, 2.5f * 0.5f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(249.0f / 255.0f, 127.0f / 255.0f, 37.0f / 255.0f)); // Naranja
		glDrawArrays(GL_TRIANGLES, 0, 36); // Pata L

		modelOp = glm::translate(tempPollo, glm::vec3(0.0f, 5.0f / 4.0f, 2.5f/2.0f + (2.5f * 0.6f)/2.0f));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f*0.6f, 5.0f*0.1, 2.5f*0.6f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(249.0f / 255.0f, 127.0f / 255.0f, 37.0f / 255.0f)); // Naranja
		glDrawArrays(GL_TRIANGLES, 0, 36); // Pico

		modelOp = glm::translate(tempPollo, glm::vec3((2.5f / 2.0f) + (2.5f * 0.05f) / 2.0f, (5.0f / 4.0f), 2.5f / 4.0f));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f*0.1, 5.0f*0.1, 2.5f*0.1));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f)); //negro
		glDrawArrays(GL_TRIANGLES, 0, 36); // Ojo R

		modelOp = glm::translate(tempPollo, glm::vec3(-1*((2.5f / 2.0f) + (2.5f * 0.05f) / 2.0f), (5.0f / 4.0f), 2.5f / 4.0f));
		modelOp = glm::scale(modelOp, glm::vec3(2.5f * 0.1, 5.0f * 0.1, 2.5f * 0.1));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f)); //negro
		glDrawArrays(GL_TRIANGLES, 0, 36); // Ojo L
		glBindVertexArray(0);
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
void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotX -= 0.2f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotX += 0.2f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 0.2f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 0.2f;
	if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
		rotZ -= 0.2f;
	if (glfwGetKey(window, GLFW_KEY_END) == GLFW_PRESS)
		rotZ += 0.2f;

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}