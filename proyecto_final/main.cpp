#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <texture.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor *monitors;
GLuint VBO[2], VAO[2];

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(-1.0f, -1.0f, 0.0f);

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 40.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

float scale = 10.0f;

void getResolution() {
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData() {

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);

	GLfloat cubeVertexCoordsBuffer[] = {
		//Position				
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

	GLfloat cubeTextureCoordsBuffer[] = {
		// Coord
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexCoordsBuffer), cubeVertexCoordsBuffer, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeTextureCoordsBuffer), cubeTextureCoordsBuffer, GL_DYNAMIC_DRAW);

	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

unsigned int texture_asphalt;
unsigned int texture_grass;
unsigned int texture_sidewalk;

void loadTextures() {
	TextureLoad texture;
	texture_asphalt = texture.generate("textures/asphalt.jpg", false);
	texture_grass = texture.generate("textures/grass.bmp", false);
	texture_sidewalk = texture.generate("textures/stone.png", false);
}

int main() {

	glfwInit();

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader shaderStatic("shaders/shader_static.vs", "shaders/shader_static.fs");
	Shader skyboxShader("shaders/shader_skybox.vs", "shaders/shader_skybox.fs");

	vector<std::string> faces = {
		"resources/skybox/sh_ft.png",
		"resources/skybox/sh_bk.png",
		"resources/skybox/sh_up.png",
		"resources/skybox/sh_dn.png",
		"resources/skybox/sh_rt.png",
		"resources/skybox/sh_lf.png"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	// -----------
	Model Asphalt("resources/models/Asphalt/Asphalt.obj");
	Model BasketHoop("resources/models/BasketBallHoop/BasketballHoop.obj");
	Model BasketField("resources/models/BasketballField/BasketballField.obj");
	Model BasketBall("resources/models/BasketballBall/Basketball.obj");
	Model Grass("resources/models/Grass/Grass.obj");
	Model Swing("resources/models/Swing/Swing.obj");
	Model Banca("resources/models/ParkBench/ParkBench.obj");
	Model testModel("resources/models/Jeep/Jeep.obj");

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window)) {	
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// render
		// ------
		glClearColor(0.1f, 0.2f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderStatic.use();
		
		//Setup Advanced Lights
		shaderStatic.setVec3("viewPos", camera.Position);
		shaderStatic.setVec3("dirLight.direction", lightDirection);
		shaderStatic.setVec3("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shaderStatic.setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderStatic.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		shaderStatic.setVec3("pointLight[0].position", lightPosition);
		shaderStatic.setVec3("pointLight[0].ambient", glm::vec3(0.6f, 0.6f, 0.6f));
		shaderStatic.setVec3("pointLight[0].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderStatic.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		shaderStatic.setFloat("pointLight[0].constant", 0.7f);
		shaderStatic.setFloat("pointLight[0].linear", 0.7f);
		shaderStatic.setFloat("pointLight[0].quadratic", 0.7f);

		shaderStatic.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		shaderStatic.setMat4("projection", projection);
		shaderStatic.setMat4("view", view);

		//Plano Asfalto
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-53.07f * scale, -0.1f, 9.77f * scale));
		model = glm::scale(model, glm::vec3(0.005348f * scale, 1.0f, 0.003904f * scale));
		shaderStatic.setMat4("model", model);
		Asphalt.Draw(shaderStatic);

		//Asfalto (Cambiar?)
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-78.045f * scale, -0.1f, 9.77f * scale));
		model = glm::scale(model, glm::vec3(0.00467f * scale, 1.0f, 0.003904f * scale));
		shaderStatic.setMat4("model", model);
		Asphalt.Draw(shaderStatic);

		//Cesped
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-78.045f * scale, -2.6f, 9.77f * scale));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0567f * scale));
		shaderStatic.setMat4("model", model);
		Grass.Draw(shaderStatic);

		//Columpio
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-83.045f * scale, 1.7f, 15.0f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f * scale));
		shaderStatic.setMat4("model", model);
		Swing.Draw(shaderStatic);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-83.045f * scale, 1.7f, 10.0f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f * scale));
		shaderStatic.setMat4("model", model);
		Swing.Draw(shaderStatic);

		//Bancas
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-75.045f * scale, 1.0f, 5.0f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0125f * scale));
		shaderStatic.setMat4("model", model);
		Banca.Draw(shaderStatic);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-79.045f * scale, 1.0f, 5.0f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0125f * scale));
		shaderStatic.setMat4("model", model);
		Banca.Draw(shaderStatic);

		//Aros de Basketball
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-415.0f, 0.0f, 99.5f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		shaderStatic.setMat4("model", model);
		BasketHoop.Draw(shaderStatic);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-647.0f, 0.0f, 96.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		shaderStatic.setMat4("model", model);
		BasketHoop.Draw(shaderStatic);

		//Cancha
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-53.07f * scale, 0.0f, 9.77f * scale));
		model = glm::scale(model, glm::vec3(0.01f * scale, 1.0f, 0.0104f * scale));
		shaderStatic.setMat4("model", model);
		BasketField.Draw(shaderStatic);

		//Pelota Basket
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 00.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		shaderStatic.setMat4("model", model);
		BasketBall.Draw(shaderStatic);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-53.07f * scale, 3.0f, 9.77f * scale));
		model = glm::scale(model, glm::vec3(0.1f));
		shaderStatic.setMat4("model", model);
		BasketBall.Draw(shaderStatic);



		model = glm::translate(glm::mat4(1.0f), glm::vec3(lightPosition.x, lightPosition.y - 20, lightPosition.z));
		model = glm::scale(model, glm::vec3(0.05f));
		shaderStatic.setMat4("model", model);
		testModel.Draw(shaderStatic);
		
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		if (deltaTime < LOOP_TIME) {
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	skybox.Terminate();
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}