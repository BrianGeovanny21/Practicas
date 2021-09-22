#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600; //altura y anchura de la ventana

// Shaders
const GLchar* vertexShaderSource = 
{
	"#version 330 core\n"
	"layout (location = 0) in vec3 position;\n" //le digo que quiero que lea la localizacion 0, y que lea un vector3 llamado position
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n" //esto es lo que le vamos a pasar al fragment shader (el ultimo es un valor para homogeneizar las operaciones en OpenGL)
	"}\0" 
};
const GLchar* fragmentShaderSource = 
{
	"#version 330 core\n"
	"out vec4 color;\n" //en forma de vec4 vamos a desplegar una variable de color
	"void main()\n"
	"{\n"
	"color = vec4(0.262f, 0.815f, 0.533f, 1.0f);\n" //de este color (este es el color de la forma)
	"}\n\0"
};

// Funciones de configuracion del shader

void CrearShader(void);




int main() {
	glfwInit();
	//Verificación de compatibilidad 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //Para maximizar la ventana

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1", NULL, NULL);
	
	//int screenWidth, screenHeight; //alto y ancho total de la pantalla

	//glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificación de errores de creacion  ventana
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		//return EXIT_FAILURE;
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
	//glViewport(0, 0, screenWidth, screenHeight); //ventana en donde vamos a dibujar

	CrearShader(); //al principio, esta función estaba comentada

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =    //esta como tal es la geometria de las figuras que yo quiero dibujar (vertices)
	{
		/*-0.5f, -0.5f, 0.0f, // Left
		0.5f, -0.5f, 0.0f, // Right
		0.0f,  0.5f, 0.0f  // Top*/

		-0.03f, 0.49f, 0.0f, //A
		-0.17f, 0.46f, 0.0f, //B
		-0.28f, 0.4f, 0.0f, //C
		-0.35f, 0.32f, 0.0f, //D
		-0.39f, 0.23f, 0.0f, //E
		-0.42f, 0.15f, 0.0f, //F
		-0.43f, 0.06f, 0.0f, //G
		-0.42f, -0.05f, 0.0f, //H
		-0.4f, -0.12f, 0.0f, //I
		-0.35f, -0.19f, 0.0f, //J          Letra G
		-0.27f, -0.25f, 0.0f, //K
		-0.14f, -0.26f, 0.0f, //L
		-0.02f, -0.19f, 0.0f, //M
		0.0f, -0.08f, 0.0f, //N
		0.01f, 0.0f, 0.0f, //O
		-0.1f, 0.0f, 0.0f, //P
		-0.2f, 0.0f, 0.0f,//Q


		0.15f, -0.26f, 0.0f, //R
		0.15f, 0.5f, 0.0f, //S             Letra N
		0.55f, -0.26f, 0.0f, //T
		0.55f, 0.5f, 0.0f, //U
	};


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO); //generamos un arreglo de vertices para el VAO y lo alojo en memoria
	glGenBuffers(1, &VBO); //generamos un buffer para el VBO y lo alojo en memoria
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO); //lo enlazamos (cargamos) a memoria

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //aqui empezamos a llenar el buffer

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	//(localidad de mem donde voy a guardar info, # de elementos, tipo de elemento, clase de enlace, corrimiento de memoria (cantidad de elem que voy a estar tomando), a partir de que elemento voy a empezar a tomar)
	glEnableVertexAttribArray(0); //lo habilitamos en memoria

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	//arriba, lo mandamos a buffer

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	//arriba, lo desenlazo

	
	


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer (este es el color del fondo)
		glClearColor(0.345f, 0.588f, 0.792f, 1.0f); //Aqui elegimos el color de la ventana (RGB) y canal alpha (para homologar valores)
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3); //Para el triangulo

		glDrawArrays(GL_LINE_STRIP, 0, 17); //Dibujamos la letra G

		glDrawArrays(GL_LINE_STRIP, 17, 4); //Dibujamos la letra N

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
	glViewport(0, 0, width, height); //ventana de consola
	//glViewport(0, 0, screenWidth, screenHeight);
}
void CrearShader()
{
    // Creamos el vertex shader y guardamos su identificador
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //Estamos creando el vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //permite alojarlo en memoria (al vertex shader)
	glCompileShader(vertexShader);


	// Verificamos los errores en tiempo de ejecución
	GLint success;
	GLchar infoLog[512];


	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// Creamos el fragment shader y guardamos su identificador
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //creamos el fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Verificamos los errores en tiempo de ejecución

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Creamos un nuevo programa y se asignamos
	// sus correspondientes vertex y fragment shaders
	GLuint shaderProgram = glCreateProgram();  //a partir de aqui creamos el programa
	glAttachShader(shaderProgram, vertexShader); //trae a ambos y los liga (une)
	glAttachShader(shaderProgram, fragmentShader); //trae a ambos y los liga
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram); //lo compila (esta parte)

	// Verificamos que no hay error en el programa
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


}

