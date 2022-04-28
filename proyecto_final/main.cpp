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
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void loadData();
void loadTextures();

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor *monitors;
GLuint VBO[2], VAO[1];

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(-1.0f, -1.0f, 0.0f);

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float	rulerSizeX = 5.0f,
		rulerSizeY = 5.0f,
		rulerSizeZ = 5.0f,
		rulerSizeStep = 2.5f;

float	rulerPositionX = 5.0f,
		rulerPositionY = 5.0f,
		rulerPositionZ = 5.0f,
		rulerPositionStep = 2.5f;

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

void loadData() {

	glGenVertexArrays(1, VAO);
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeTextureCoordsBuffer), cubeTextureCoordsBuffer, GL_STATIC_DRAW);

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

	loadData();
	loadTextures();

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader shaderStatic("shaders/shader_static.vs", "shaders/shader_static.fs");
	Shader shaderSkybox("shaders/shader_skybox.vs", "shaders/shader_skybox.fs");
	Shader shaderCube("shaders/shader_texture_color.vs", "shaders/shader_texture_color.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

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
	shaderSkybox.use();
	shaderSkybox.setInt("skybox", 0);

	// load models
	// -----------
	Model Asphalt("resources/models/Asphalt/Asphalt.obj");
	Model BasketHoop("resources/models/BasketBallHoop/BasketballHoop.obj");
	Model BasketField("resources/models/BasketballField/BasketballField.obj");
	Model BasketBall("resources/models/BasketballBall/Basketball.obj");
	Model Grass("resources/models/Grass/Grass.obj");
	Model Greens("resources/models/Greens/Greens.obj");
	Model Swing("resources/models/Swing/Swing.obj");
	Model Banca("resources/models/ParkBench/ParkBench.obj");
	Model Sidewalk("resources/models/Sidewalk/Sidewalk.obj");
	Model Path("resources/models/Path/Path.obj");
	Model Pool("resources/models/SwimmingPool/Pool.obj");
	Model Water("resources/models/Water/Water.obj");
	Model HouseThree("resources/models/HouseThreeFloor/HouseThree.obj");
	Model Kite("resources/models/Kite/Kite.obj");

	Model testModel("resources/models/Grass/Grass.obj");


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window)) {

		shaderSkybox.setInt("skybox", 0);

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

		// Calle 1
		for (int i = 0; i <= 3; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(-7.5f * i * scale, -0.1f, -3.75f * scale));
			model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 7.5f * scale, 1.0f, 1.0f / 5000.0f * 7.5f * scale));
			shaderStatic.setMat4("model", model);
			Asphalt.Draw(shaderStatic);
		}

		// Calle 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-29.285f * scale, -0.1f, -3.75f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 6.07f * scale, 1.0f, 1.0f / 5000.0f * 7.5f * scale));
		shaderStatic.setMat4("model", model);
		Asphalt.Draw(shaderStatic);

		// Calle 1
		for (int i = 0; i <= 3; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(7.5f * i * scale, -0.1f, -3.75f * scale));
			model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 7.5f * scale, 1.0f, 1.0f / 5000.0f * 7.5f * scale));
			shaderStatic.setMat4("model", model);
			Asphalt.Draw(shaderStatic);
		}

		// Calle 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(29.305f * scale, -0.1f, -3.75f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 6.11f * scale, 1.0f, 1.0f / 5000.0f * 7.5f * scale));
		shaderStatic.setMat4("model", model);
		Asphalt.Draw(shaderStatic);

		// Calle 2
		for (int i = 0; i <= 3; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(39.515f * scale, -0.1f, (-3.75f - 14.31f * i) * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 14.31f * scale, 1.0f, 1.0f / 5000.0f * 14.31f * scale));
			shaderStatic.setMat4("model", model);
			Asphalt.Draw(shaderStatic);
		}

		// Calle 2
		for (int i = 0; i <= 3; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(39.515f * scale, -0.1f, (-3.75f + 14.31f * i) * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 14.31f * scale, 1.0f, 1.0f / 5000.0f * 14.31f * scale));
			shaderStatic.setMat4("model", model);
			Asphalt.Draw(shaderStatic);
		}

		// Calle 3
		for (int i = 0; i <= 6; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(-36.07f * scale, -0.1f, (-3.75f - 7.5f * i) * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 7.5f * scale, 1.0f, 1.0f / 5000.0f * 7.5f * scale));
			shaderStatic.setMat4("model", model);
			Asphalt.Draw(shaderStatic);
		}

		// Calle 3
		for (int i = 0; i <= 6; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(-36.07f * scale, -0.1f, (-3.75f + 7.5f * i) * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 7.5f * scale, 1.0f, 1.0f / 5000.0f * 7.5f * scale));
			shaderStatic.setMat4("model", model);
			Asphalt.Draw(shaderStatic);
		}

		// Banqueta Calle 1 Izquierda
		for (int i = 0; i <= 3; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(-7.5f * i * scale, -0.1f, -8.0f * scale));
			model = glm::scale(model, glm::vec3(1.0f / 100.0f * 7.5f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
			shaderStatic.setMat4("model", model);
			Sidewalk.Draw(shaderStatic);
		}

		// Banqueta Calle 1 Izquierda
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-29.285f * scale, -0.1f, -8.0f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 100.0f * 6.07f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
		shaderStatic.setMat4("model", model);
		Sidewalk.Draw(shaderStatic);

		// Banqueta Calle 1 Izquierda
		for (int i = 0; i <= 3; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(7.5f * i * scale, -0.1f, -8.0f * scale));
			model = glm::scale(model, glm::vec3(1.0f / 100.0f * 7.5f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
			shaderStatic.setMat4("model", model);
			Sidewalk.Draw(shaderStatic);
		}

		// Banqueta Calle 1 Izquierda
		model = glm::translate(glm::mat4(1.0f), glm::vec3(29.305f * scale, -0.1f, -8.0f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 100.0f * 6.11f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
		shaderStatic.setMat4("model", model);
		Sidewalk.Draw(shaderStatic);

		// Banqueta Calle 1 Derecha
		for (int i = 0; i <= 3; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(-7.5f * i * scale, -0.1f, 0.5f * scale));
			model = glm::scale(model, glm::vec3(1.0f / 100.0f * 7.5f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
			shaderStatic.setMat4("model", model);
			Sidewalk.Draw(shaderStatic);
		}

		// Banqueta Calle 1 Derecha
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-29.285f * scale, -0.1f, 0.5f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 100.0f * 6.07f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
		shaderStatic.setMat4("model", model);
		Sidewalk.Draw(shaderStatic);

		// Banqueta Calle 1 Derecha
		for (int i = 0; i <= 3; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(7.5f * i * scale, -0.1f, 0.5f * scale));
			model = glm::scale(model, glm::vec3(1.0f / 100.0f * 7.5f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
			shaderStatic.setMat4("model", model);
			Sidewalk.Draw(shaderStatic);
		}

		// Banqueta Calle 1 Derecha
		model = glm::translate(glm::mat4(1.0f), glm::vec3(29.305f * scale, -0.1f, 0.5f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 100.0f * 6.11f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
		shaderStatic.setMat4("model", model);
		Sidewalk.Draw(shaderStatic);

		// Banqueta Calle 2 Izquierda
		for (int i = 0; i <= 3; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(47.17f * scale, -0.1f, (-3.75f + 14.31f * i) * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f / 100.0f * 14.31f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
			shaderStatic.setMat4("model", model);
			Sidewalk.Draw(shaderStatic);
		}

		// Banqueta Calle 2 Izquierda
		model = glm::translate(glm::mat4(1.0f), glm::vec3(31.86f * scale, -0.1f, 2.2025f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f / 100.0f * 2.405f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
		shaderStatic.setMat4("model", model);
		Sidewalk.Draw(shaderStatic);

		// Banqueta Calle 2 Izquierda
		for (int i = 0; i <= 3; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(47.17f * scale, -0.1f, (-3.75f - 14.31f * i) * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f / 100.0f * 14.31f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
			shaderStatic.setMat4("model", model);
			Sidewalk.Draw(shaderStatic);
		}

		// Banqueta Calle 2 Izquierda
		model = glm::translate(glm::mat4(1.0f), glm::vec3(31.86f * scale, -0.1f, -9.7025f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f / 100.0f * 2.405f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
		shaderStatic.setMat4("model", model);
		Sidewalk.Draw(shaderStatic);

		// Banqueta Calle 2 Derecha 
		for (int i = 1; i <= 3; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(31.86f * scale, -0.1f, (-3.75f + 14.31f * i) * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f / 100.0f * 14.31f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
			shaderStatic.setMat4("model", model);
			Sidewalk.Draw(shaderStatic);
		}

		// Banqueta Calle 2 Derecha
		for (int i = 1; i <= 3; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(31.86f * scale, -0.1f, (-3.75f - 14.31f * i) * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f / 100.0f * 14.31f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
			shaderStatic.setMat4("model", model);
			Sidewalk.Draw(shaderStatic);
		}

		// Banqueta Calle 3 Izquierda
		for (int i = 0; i <= 6; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.32f * scale, -0.1f, (-3.75f - 7.5f * i) * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f / 100.0f * 7.5f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
			shaderStatic.setMat4("model", model);
			Sidewalk.Draw(shaderStatic);
		}

		// Banqueta Calle 3 Izquierda
		for (int i = 0; i <= 6; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.32f * scale, -0.1f, (-3.75f + 7.5f * i) * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f / 100.0f * 7.5f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
			shaderStatic.setMat4("model", model);
			Sidewalk.Draw(shaderStatic);
		}

		// Banqueta Calle 3 Derecha
		for (int i = 1; i <= 6; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(-31.82f * scale, -0.1f, (-3.75f - 7.5f * i) * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f / 100.0f * 7.5f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
			shaderStatic.setMat4("model", model);
			Sidewalk.Draw(shaderStatic);
		}

		// Banqueta Calle 3 Derecha
		for (int i = 1; i <= 6; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(-31.82f * scale, -0.1f, (-3.75f + 7.5f * i) * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f / 100.0f * 7.5f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 1.0f * scale));
			shaderStatic.setMat4("model", model);
			Sidewalk.Draw(shaderStatic);
		}

		// Camellon 1 Concreto
		for (int i = 0; i <= 1; i++) {
			for (int j = 0; j <= 1; j++) {
				model = glm::translate(glm::mat4(1.0f), glm::vec3((38.84f + 1.35f * j) * scale, -0.1f, (10.35f + 14.1f * i) * scale));
				model = glm::rotate(model, glm::radians(90.0f + 180.0f * j), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(1.0f / 100.0f * 14.1f * scale, 1.0f / 5.0f * 0.15f * scale, 1.0f / 20.0f * 1.35f * scale));
				shaderStatic.setMat4("model", model);
				Sidewalk.Draw(shaderStatic);
			}
		}

		// Camellon 1 Pasto
		for (int i = 0; i <= 11; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(39.515f * scale, 1.5f, (4.475f + 2.35 * i) * scale));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f / 300.0f * 1.9f * scale, 1.0f / 300.0f * 2.35f * scale, 1.0f / 150.0f * scale));
			shaderStatic.setMat4("model", model);
			Grass.Draw(shaderStatic);
		}

		// Camellon 2 Concreto
		for (int i = 0; i <= 1; i++) {
			for (int j = 0; j <= 1; j++) {
				model = glm::translate(glm::mat4(1.0f), glm::vec3((38.84f + 1.35f * j) * scale, -0.1f, (-17.85f - 14.1f * i) * scale));
				model = glm::rotate(model, glm::radians(90.0f + 180.0f * j), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(1.0f / 100.0f * 14.1f * scale, 1.0f / 5.0f * 0.15f * scale, 1.0f / 20.0f * 1.35f * scale));
				shaderStatic.setMat4("model", model);
				Sidewalk.Draw(shaderStatic);
			}
		}

		// Camellon 2 Pasto
		for (int i = 0; i <= 11; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(39.515f * scale, 1.5f, (-11.975 - 2.35 * i) * scale));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f / 300.0f * 1.9f * scale, 1.0f / 300.0f * 2.35f * scale, 1.0f / 150.0f * scale));
			shaderStatic.setMat4("model", model);
			Grass.Draw(shaderStatic);
		}

		/* AREA RECREATIVA */

		

		// Plano Asfalto Debajo de Cancha
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-54.180f * scale, -0.1f, 23.90f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 26.76f * scale, 1.0f, 1.0f / 5000.0f * 19.54f * scale));
		shaderStatic.setMat4("model", model);
		Asphalt.Draw(shaderStatic);

		// Plano Asfalto Debajo de Cesped 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-79.01f * scale, -0.1f, 23.90f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 22.90f * scale, 1.0f, 1.0f / 5000.0f * 19.54f * scale));
		shaderStatic.setMat4("model", model);
		Asphalt.Draw(shaderStatic);

		// Plano Asfalto Debajo de Cesped 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-54.180f * scale, -0.1f, 3.34f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 26.76f * scale, 1.0f, 1.0f / 5000.0f * 21.58f * scale));
		shaderStatic.setMat4("model", model);
		Asphalt.Draw(shaderStatic);

		// Cesped 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-79.01f * scale, -2.6f, 23.90f * scale));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f / 300.0f * 17.0f * scale, 1.0f / 300.0f * 17.0f * scale, 1.0f / 300.0f * 17.0f * scale));
		shaderStatic.setMat4("model", model);
		Grass.Draw(shaderStatic);

		// Cesped 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-54.180f * scale, -0.1f, 3.34f * scale));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f / 300.0f * 18.93f * scale, 1.0f / 300.0f * 18.93f * scale, 1.0f / 300.0f * 18.93f * scale));
		shaderStatic.setMat4("model", model);
		Grass.Draw(shaderStatic);

		// Columpio 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-84.045f * scale, 1.7f, 27.0f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.012f * scale));
		shaderStatic.setMat4("model", model);
		Swing.Draw(shaderStatic);

		// Columpio 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-84.045f * scale, 1.7f, 21.5f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.012f * scale));
		shaderStatic.setMat4("model", model);
		Swing.Draw(shaderStatic);

		// Banca 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-76.045f * scale, 1.0f, 17.0f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0125f * scale));
		shaderStatic.setMat4("model", model);
		Banca.Draw(shaderStatic);

		// Banca 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-80.045f * scale, 1.0f, 17.0f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0125f * scale));
		shaderStatic.setMat4("model", model);
		Banca.Draw(shaderStatic);

		// Aro de Basketball 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-42.5f * scale, 0.0f, 24.05f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.01f * scale));
		shaderStatic.setMat4("model", model);
		BasketHoop.Draw(shaderStatic);

		// Aro de Basketball 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-65.7f * scale, 0.0f, 23.75f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.01f * scale));
		shaderStatic.setMat4("model", model);
		BasketHoop.Draw(shaderStatic);

		// Cancha de Basket
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-54.30f * scale, 0.05f, 23.90f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 2650.0f * 26.76f * scale, 1.0f, 1.0f / 1550.0f * 19.54f * scale));
		shaderStatic.setMat4("model", model);
		BasketField.Draw(shaderStatic);

		// Pelota de Basket
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-54.180f * scale, 3.0f, 23.90f * scale));
		model = glm::scale(model, glm::vec3(0.01f * scale));
		shaderStatic.setMat4("model", model);
		BasketBall.Draw(shaderStatic);

		// Kite
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-54.180f * scale, 6.0f, 23.90f * scale));
		model = glm::scale(model, glm::vec3(0.01f * scale));
		shaderStatic.setMat4("model", model);
		Kite.Draw(shaderStatic);

		/* AREA RESIDENCIAL */

		// Piso de Pasto
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 4; j++) {
				model = glm::translate(glm::mat4(1.0f), glm::vec3((-28.35f + 6.3f * i) * scale, -0.1f, (4.284f + 6.568f * j) * scale));
				model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 6.3f * scale, 1.0f, 1.0f / 5000.0f * 6.568f * scale));
				shaderStatic.setMat4("model", model);
				Greens.Draw(shaderStatic);
			}
		}

		// HouseThree
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-17.20f * scale, 1.0f, 10.0f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 430.0f * 20.0f * scale, 1.0f / 390.0f * 10.0f * scale, 1.0f / 710.0f * 10.0f * scale));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		HouseThree.Draw(shaderStatic);

		// HouseThree2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-17.20f * scale, 1.0f, 25.0f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 430.0f * 20.0f * scale, 1.0f / 390.0f * 10.0f * scale, 1.0f / 710.0f * 10.0f * scale));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		HouseThree.Draw(shaderStatic);

		/* AREA COMUN */

		// Piso de Pasto
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 8; j++) {
				model = glm::translate(glm::mat4(1.0f), glm::vec3((-28.35f + 6.3f * i) * scale, -0.1f, (-11.715f - 6.43f * j) * scale));
				model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 6.3f * scale, 1.0f, 1.0f / 5000.0f * 6.43f * scale));
				shaderStatic.setMat4("model", model);
				Greens.Draw(shaderStatic);
			}
		}

		// Camino 1
		for (int i = 0; i <= 3; i++) {
			for (int j = 0; j <= 24; j++) {
				model = glm::translate(glm::mat4(1.0f), glm::vec3((-2.055f + 1.37f * i) * scale, 0.0f, (-9.162f - 1.324f * j) * scale));
				model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 1.37f * scale, 1.0f, 1.0f / 5000.0f * 1.324f * scale));
				shaderStatic.setMat4("model", model);
				Path.Draw(shaderStatic);
			}
		}

		// Camino 2
		for (int i = 0; i <= 3; i++) {
			for (int j = 0; j <= 25; j++) {
				model = glm::translate(glm::mat4(1.0f), glm::vec3((-2.078f + 1.324f * j) * scale, 0.0f, (-42.285f - 1.37f * i) * scale));
				model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 1.37f * scale, 1.0f, 1.0f / 5000.0f * 1.324f * scale));
				shaderStatic.setMat4("model", model);
				Path.Draw(shaderStatic);
			}
		}

		// Camino a Alberca
		for (int i = 0; i <= 3; i++) {
			for (int j = 0; j <= 7; j++) {
				model = glm::translate(glm::mat4(1.0f), glm::vec3((-3.365f - 1.25f * i) * scale, 0.0f, (-12.075f - 1.25f * j) * scale));
				model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 1.25f * scale, 1.0f, 1.0f / 5000.0f * 1.25f * scale));
				shaderStatic.setMat4("model", model);
				Path.Draw(shaderStatic);
			}
		}

		// Alberca
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-17.20f * scale, 2.25f, -16.45f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 92.5f * 20.0f * scale, 1.0f / 97.0f * 10.0f * scale, 1.0f / 52.5f * 10.0f * scale));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		Pool.Draw(shaderStatic);

		// Agua de Alberca
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-17.20f * scale, 0.85f, -16.45f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 19.0f * scale, 1.0f, 1.0f / 5000.0f * 9.0f * scale));
		shaderStatic.setMat4("model", model);
		Water.Draw(shaderStatic);

		/* FIN DE AREAS */

		// Modelo de Prueba
		model = glm::translate(glm::mat4(1.0f), glm::vec3(lightPosition.x, lightPosition.y - 20.0f, lightPosition.z));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f / 300.0f * 50.0f, 1.0f / 300.0f * 50.0f, 1.0f / 100.0f));
		shaderStatic.setMat4("model", model);
		testModel.Draw(shaderStatic);

		shaderCube.use();

		// view/projection transformations
		shaderCube.setMat4("projection", projection);
		shaderCube.setMat4("view", view);

		glBindVertexArray(VAO[0]);
		glBindTexture(GL_TEXTURE_2D, texture_asphalt);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(rulerPositionX, rulerPositionY, rulerPositionZ));
		model = glm::scale(model, glm::vec3(rulerSizeX, rulerSizeY, rulerSizeZ));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		shaderSkybox.use();
		skybox.Draw(shaderSkybox, view, projection, camera);
		
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
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		rulerSizeX += rulerSizeStep;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		rulerSizeY += rulerSizeStep;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		rulerSizeZ += rulerSizeStep;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		rulerSizeStep *= -1;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		std::cout << "Size is: " << rulerSizeX << ", " << rulerSizeY << ", " << rulerSizeZ << std::endl;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		rulerPositionX += rulerPositionStep;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		rulerPositionY += rulerPositionStep;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		rulerPositionZ += rulerPositionStep;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		rulerPositionStep *= -1;
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