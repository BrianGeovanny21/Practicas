#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificación de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

	Shader ourShader("Shader/core.vs", "Shader/core.frag"); //creamos la variable "ourShader" de tipo shader que recibe 2 archivos (el vertex y el fragment)

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		-0.6f,  0.3f, 0.0f,    1.0f,0.0f,0.0f, // A
		-0.3f, 0.3f, 0.0f,    1.0f,1.0f,0.0f, // B
		-0.3f, 0.6f, 0.0f,   1.0f,0.0f,1.0f,  // C    Trapecio
		-0.6f,  0.6f, 0.0f,   1.0f,1.0f,0.0f, // D
		0.0f,   0.3f, 0.0f,   1.0f,1.0f,0.0f, //E
		-0.9f,  0.3f, 0.0f,   1.0f,1.0f,0.0f, //F


		-0.5f,  0.0f, 0.0f,   1.0f,0.0f,0.0f, //G
		-0.2f, -0.4f, 0.0f,   1.0f,1.0f,0.0f, // H
		-0.8f, -0.4f, 0.0f,   1.0f,0.0f,1.0f, // I
		-0.3f, -0.9f, 0.0f,   1.0f,1.0f,0.0f, // J    Pentagono
		-0.7f, -0.9f, 0.0f,   1.0f,1.0f,0.0f, //K
		-0.5f, -0.4f, 0.0f,   1.0f,1.0f,0.0f, //L


		0.3f, 0.3f, 0.0f,   1.0f,0.0f,0.0f, // M
		0.6f, 0.9f, 0.0f,   1.0f,1.0f,0.0f, // N     Triangulo
		0.9f, 0.3f, 0.0f,   1.0f,0.0f,1.0f, // O


		0.5f,  0.0f, 0.0f,  1.0f,0.0f,0.0f, // P
		0.3f, -0.5f, 0.0f,  1.0f,1.0f,0.0f, // Q     Rombo
		0.5F, -1.0f, 0.0f,  1.0f,1.0f,0.0f, // S  (este aqui porque si no no hace correctamenta la figura)
		0.7f, -0.5f, 0.0f,  1.0f,0.0f,1.0f, // R
		
		
	};
	unsigned int indices[] = {  // note that we start from 0!  ; estos son los indices para el EBO
		0,1,3, //Trapecio
		3,1,2,
		2,1,4,
		3,0,5,

		6,7,11, //Pentagono
		11,7,9,
		11,9,10,
		11,10,8,
		11,8,6,
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO); //VAO 
	glGenBuffers(1, &VBO); //ES UN BUFFER (ES UN ARREGLO DE VERTICES)
	glGenBuffers(1, &EBO); //aqui ya aparece la creacion del EBO, ES UN ARREGLO DE BUFFERS

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO); //Aqui enlazamos a memoria

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion (Localidades de memoria)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	//vamos a trabajar en la localidad 0, con 3 elementos, de tipo flotante, de los 6 que estan disponibles en el arreglo de vertices, empezando desde el elemento 0
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	//vamos a trabajar en la localidad 1, con 3 elementos, de tipo flotante, de los 6 que estan disponibles en el arreglo de vertices, empezando desde el elemento 3 (que seria el cuarto)
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //lo mandamos a memoria


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	//lo desenlazo

	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use(); //aqui mandamos a llamar al shader (otros archivos)
		glBindVertexArray(VAO); //jala la informacion del shader

		glPointSize(10); //para cambiar el tamaño de los puntos

		//Dibujo Trapecio
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); //mandamos a dibujar (trabaja con los indices del EBO, estan mas arriba)
		//Para dibujar el segundo triangulo contenido en los indices(segundo vector del EBO, debo hacer un corrimiento de memoria: (GLvoid *)(3*sizeof(GLfloat))
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(3 * sizeof(GLfloat)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(6 * sizeof(GLfloat)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(9 * sizeof(GLfloat)));

		//Dibujo Pentagono
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(12 * sizeof(GLfloat)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(15 * sizeof(GLfloat)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(18 * sizeof(GLfloat)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(21 * sizeof(GLfloat)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(24 * sizeof(GLfloat)));

		//glDrawArrays(GL_TRIANGLES,0,3); //trabaja directamente con los vertices del VAO (de la geometría de la figura)
		glDrawArrays(GL_LINE_LOOP, 12, 3); //Dibujo triangulo

		glDrawArrays(GL_LINE_LOOP, 15, 4); //Dibujo rombo
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}