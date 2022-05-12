/*-----------------------------------------------------------------------*/
/*                         Proyecto Final CGeIHC                         */
/*                                2022-2                                 */
/*                         Elaborado por Alumnos:                        */
/*                       - Cesar Ambrosio Martinez                       */
/*                       - Luis Mario Perez Salda�a                      */
/*                          - Huberto Rios Nunez                         */
/*-----------------------------------------------------------------------*/

#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <AL/al.h>
#include <Al/alc.h>
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <audio_file.h>
#include <audio_format.h>
#include <texture.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <torus.h>

#include <iostream>
#include <string>

#include "textures_baby_yoda.h"
#include "textures_mike_wazowski.h"
#include "textures_aang.h"

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
Camera camera(glm::vec3(0.0f, 10.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float scale = 10.0f;

float	rulerSizeX = 5.0f,
		rulerSizeY = 5.0f,
		rulerSizeZ = 5.0f,
		rulerSizeStep = 2.5f;

float	rulerPositionX = 0.0f,
		rulerPositionY = 0.0f,
		rulerPositionZ = 0.0f,
		rulerPositionStep = 2.5f;

float	modelPositionX = -84.045f * scale,
		modelPositionY = 2.0f * scale,
		modelPositionZ = 21.5f * scale,
		modelPositionStep = 0.005f * scale;

float baby_yoda_body_rotate = 0.0f;
float baby_yoda_left_arm_rotate_y = 20.0f;
float baby_yoda_left_arm_rotate_z = 40.0f;
float baby_yoda_right_arm_rotate_y = -20.0f;
float baby_yoda_right_arm_rotate_z = -40.0f;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

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

ALuint buffers[2];
ALuint song_buffers[4];
ALuint sources[3];

int current_song_index;
glm::vec3 speakers_position = glm::vec3(-17.30f * scale, 1.1f * scale, -25.60f * scale);

void load_song_with_index(int index) {
	ALenum alError;
	current_song_index = index;
	alSourceStop(sources[0]);
	alSourcei(sources[0], AL_BUFFER, song_buffers[index]);
	alSourcePlay(sources[0]);
	alError = alGetError();
	if (alError != AL_NO_ERROR) {
		std::cerr << ("alSource :", alError) << std::endl;
		return;
	}
}

void load_next_song() {
	current_song_index = (current_song_index + 1) % 4;
	load_song_with_index(current_song_index);
}

void loadAudio() {

	ALenum alError;
	ALCenum alcError;

	ALCdevice* openALDevice = alcOpenDevice(NULL);
	if (!openALDevice) return;

	ALCcontext* openALContext;
	openALContext = alcCreateContext(openALDevice, NULL);
	alcMakeContextCurrent(openALContext);
	alcError = alcGetError(openALDevice);
	if (alcError != ALC_NO_ERROR) {
		std::cerr << ("alContext :", alcError) << std::endl;
		return;
	}

	alGenBuffers(2, buffers);
	alGenBuffers(4, song_buffers);
	alError = alGetError();
	if (alError != AL_NO_ERROR) {
		std::cerr << ("alGenBuffers :", alError) << std::endl;
		return;
	}

	AudioFile audio_ozuna;
	char* audio_ozuna_buffer = audio_ozuna.load("audios/audio_ozuna_adicto.wav");
	ALenum audio_ozuna_format = get_audio_format(audio_ozuna.channels, audio_ozuna.bitsPerSample);
	alBufferData(song_buffers[0], audio_ozuna_format, audio_ozuna_buffer, audio_ozuna.size, audio_ozuna.sampleRate);

	AudioFile audio_robin_schulz;
	char* audio_robin_schulz_buffer = audio_robin_schulz.load("audios/audio_robin_schulz_sugar.wav");
	ALenum audio_robin_schulz_format = get_audio_format(audio_robin_schulz.channels, audio_robin_schulz.bitsPerSample);
	alBufferData(song_buffers[1], audio_robin_schulz_format, audio_robin_schulz_buffer, audio_robin_schulz.size, audio_robin_schulz.sampleRate);

	AudioFile audio_lilly_wood;
	char* audio_lilly_wood_buffer = audio_lilly_wood.load("audios/audio_lilly_wood_prayer.wav");
	ALenum audio_lilly_wood_format = get_audio_format(audio_lilly_wood.channels, audio_lilly_wood.bitsPerSample);
	alBufferData(song_buffers[2], audio_lilly_wood_format, audio_lilly_wood_buffer, audio_lilly_wood.size, audio_lilly_wood.sampleRate);

	AudioFile audio_travis_scott;
	char* audio_travis_scott_buffer = audio_travis_scott.load("audios/audio_travis_scott_goosebumps.wav");
	ALenum audio_travis_scott_format = get_audio_format(audio_travis_scott.channels, audio_travis_scott.bitsPerSample);
	alBufferData(song_buffers[3], audio_travis_scott_format, audio_travis_scott_buffer, audio_travis_scott.size, audio_travis_scott.sampleRate);

	AudioFile audio_nature;
	char* audio_nature_buffer = audio_nature.load("audios/audio_naturaleza.wav");
	ALenum audio_nature_format = get_audio_format(audio_nature.channels, audio_nature.bitsPerSample);
	alBufferData(buffers[0], audio_nature_format, audio_nature_buffer, audio_nature.size, audio_nature.sampleRate);

	AudioFile audio_kids_playing;
	char* audio_kids_playing_buffer = audio_kids_playing.load("audios/audio_ninos_jugando.wav");
	ALenum audio_kids_playing_format = get_audio_format(audio_kids_playing.channels, audio_kids_playing.bitsPerSample);
	alBufferData(buffers[1], audio_kids_playing_format, audio_kids_playing_buffer, audio_kids_playing.size, audio_kids_playing.sampleRate);

	alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	alError = alGetError();
	if (alError != AL_NO_ERROR) {
		std::cerr << ("alDistanceModel :", alError) << std::endl;
		return;
	}

	alGenSources(3, sources);
	alError = alGetError();
	if (alError != AL_NO_ERROR) {
		std::cerr << ("alGenSources :", alError) << std::endl;
		return;
	}

	// Audio Bocinas
	alSourcef(sources[0], AL_PITCH, 1);
	alSourcef(sources[0], AL_GAIN, 5.0f);
	alSource3f(sources[0], AL_POSITION, speakers_position.x, speakers_position.y, speakers_position.z);
	alSourcef(sources[0], AL_REFERENCE_DISTANCE, 15.0f * scale);
	alSourcef(sources[0], AL_ROLLOFF_FACTOR, 400.0f);
	alSource3f(sources[0], AL_VELOCITY, 0, 0, 0);
	alSourcei(sources[0], AL_LOOPING, AL_TRUE);
	alError = alGetError();
	if (alError != AL_NO_ERROR) {
		std::cerr << ("alSource :", alError) << std::endl;
		return;
	}

	// Audio Naturaleza
	alSourcef(sources[1], AL_PITCH, 1);
	alSourcef(sources[1], AL_GAIN, 5.0f);
	alSource3f(sources[1], AL_POSITION, camera.Center.x, camera.Center.y, camera.Center.z);
	alSource3f(sources[1], AL_VELOCITY, 0, 0, 0);
	alSourcei(sources[1], AL_LOOPING, AL_TRUE);
	alSourcei(sources[1], AL_BUFFER, buffers[0]);
	alError = alGetError();
	if (alError != AL_NO_ERROR) {
		std::cerr << ("alSource :", alError) << std::endl;
		return;
	}

	// Audio Ninos Jugando
	alSourcef(sources[2], AL_PITCH, 1);
	alSourcef(sources[2], AL_GAIN, 4.5f);
	alSource3f(sources[2], AL_POSITION, -54.180f * scale, 3.0f, 23.90f * scale);
	alSourcef(sources[2], AL_REFERENCE_DISTANCE, 20.0f * scale);
	alSourcef(sources[2], AL_ROLLOFF_FACTOR, 70.0f);
	alSource3f(sources[2], AL_VELOCITY, 0, 0, 0);
	alSourcei(sources[2], AL_LOOPING, AL_TRUE);
	alSourcei(sources[2], AL_BUFFER, buffers[1]);
	alError = alGetError();
	if (alError != AL_NO_ERROR) {
		std::cerr << ("alSource :", alError) << std::endl;
		return;
	}
	
	alListener3f(AL_POSITION, camera.Center.x, camera.Center.y, camera.Center.z);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerf(AL_GAIN, 0.99f);

}

unsigned int texture_baby_yoda;
unsigned int texture_aang;
unsigned int texture_mike_wazowski;
unsigned int texture_pool_float;
unsigned int texture_donut;
unsigned int texture_swing_lifesaver;
unsigned int texture_fire;

void loadTextures() {
	TextureLoad texture;
	texture_baby_yoda = texture.generate("textures/yoda.png", true);
	texture_mike_wazowski = texture.generate("textures/mike_face.jpg", false);
	texture_aang = texture.generate("textures/aang_texture.png", true);
	texture_pool_float = texture.generate("textures/blue_white_stripes.jpg", false);
	texture_donut = texture.generate("textures/donut.jpg", false);
	texture_swing_lifesaver = texture.generate("textures/orange_yellow_stripes.jpg", false);
	texture_fire = texture.generate("textures/fire.png", true);
}

// Animacion Hojas
float leaf_offset_x = 0.0f;
float leaf_offset_y = 0.0f;
float leaf_offset_z = 0.0f;
float leaf_rotation = 0.0f;
float leaf_static_time = 0.0f;
enum LEAF_DIRECTION {
	LEAF_LEFT_TO_RIGHT,
	LEAF_RIGHT_TO_LEFT,
	LEAF_STATIC,
};
LEAF_DIRECTION leaf_direction = LEAF_LEFT_TO_RIGHT;

// Animacion Cometa
float kite_tail_rotation_offset_x = 0.0f;
float kite_tail_rotation_offset_z = 0.0f;
float kite_tail_move_time = 0.0f;
int kite_wind_strength = 2;
int kite_wind_change = 1;
float kite_wind_strength_change_time = 0.0f;

// Animacion Columpio
float swing_rotation = 0.0f;
float swing_angle_limit = 5.0f;
bool swing_angle_change = false;
bool swing_stopping = false;
float swing_static_time = 0.0f;
enum SWING_DIRECTION {
	SWING_MOVE_FRONT,
	SWING_MOVE_BACK,
	SWING_STATIC
};
SWING_DIRECTION swing_direction = SWING_STATIC;
enum SWING_MOVEMENT {
	SWING_ACCELERATE,
	SWING_DEACCELERATE,
};
SWING_MOVEMENT swing_movement = SWING_ACCELERATE;

// Baby Yoda Animation
float baby_yoda_offset_y = 0.0f;
float baby_yoda_last_offset_y = 0.0f;
float baby_yoda_delta_offset_y = 0.0f;
bool baby_yoda_levitating = false;
enum BABY_YODA_LEVITATION_STAGE {
	BABY_YODA_PREPARING_ARMS,
	BABY_YODA_LOWERING_ARMS,
	BABY_YODA_FORWARD_ARMS,
	BABY_YODA_WAVING_ARMS,
	BABY_YODA_TO_NORMAL_ARMS,
};
BABY_YODA_LEVITATION_STAGE baby_yoda_levitation_stage = BABY_YODA_PREPARING_ARMS;
float baby_yoda_initial_offset_y;
float baby_yoda_initial_left_arm_rotate_y;
float baby_yoda_initial_left_arm_rotate_z;
float baby_yoda_initial_right_arm_rotate_y;
float baby_yoda_initial_right_arm_rotate_z;
float baby_yoda_initial_time;
bool baby_yoda_should_save_initial_values = true;
enum BABY_YODA_WAVE_DIRECTION {
	BABY_YODA_WAVE_DOWN,
	BABY_YODA_WAVE_UP,
};
BABY_YODA_WAVE_DIRECTION baby_yoda_wave_direction = BABY_YODA_WAVE_DOWN;

float pool_float_offset_x = 0.0f;
float pool_float_offset_z = 0.0f;
float pool_float_angle = 15.0f;
float pool_float_speed = 0.5f;
float pool_float_move_time = 0.0f;

glm::vec3 x_wing_position = glm::vec3(-78.045f * scale, 10.0f * scale, 22.0f * scale);
float x_wing_movement_radius = 10.0f * scale;
float x_wing_offset_x = 0.0f;
float x_wing_offset_z = 0.0f;
float x_wing_angle = 0.0f;
float x_wing_rotate = 0.0f;
float x_wing_initial_time = 0.0f;
float x_wing_initial_rotate = 0.0f;
bool x_wing_should_save_initial_values = false;
enum X_WING_MOVEMENT {
	X_WING_STRAIGHT_LINE,
	X_WING_ROTATING
};
X_WING_MOVEMENT x_wing_movement = X_WING_STRAIGHT_LINE;

//Animacion Fuego
float fire_rotation = 0.0f;

void runAnimations() {

	// Animaciones de Hojas
	if (leaf_direction == LEAF_LEFT_TO_RIGHT) {
		leaf_rotation = (leaf_offset_z) * (3.0f - leaf_offset_z) * 2.5f;
		leaf_offset_z += (deltaTime * 0.001f * 3.0f) / 0.5f;
		if (leaf_offset_z >= 3.0f) {
			leaf_direction = LEAF_RIGHT_TO_LEFT;
		}
	}
	if (leaf_direction == LEAF_RIGHT_TO_LEFT) {
		leaf_rotation = -1.0 * (leaf_offset_z) * (3.0f + leaf_offset_z) * 2.5f;
		leaf_offset_z -= (deltaTime * 0.001f * 3.0f) / 0.5f;
		if (leaf_offset_z <= -3.0f) {
			leaf_direction = LEAF_LEFT_TO_RIGHT;
		}
	}
	if (leaf_direction == LEAF_STATIC) {
		leaf_static_time += (deltaTime * 0.001f) / 2.0f;
		if (leaf_static_time >= 1.0f) {
			leaf_offset_x = 0.0f;
			leaf_offset_y = 0.0f;
			leaf_offset_z = 0.0f;
			leaf_rotation = 0.0f;
			leaf_static_time = 0;
			leaf_direction = LEAF_LEFT_TO_RIGHT;
		}
	}
	if (leaf_offset_y > -4.9f) {
		leaf_offset_y -= (deltaTime * 0.001f * 5.0f) / 5.0f;
	}
	if (leaf_offset_y <= -4.9f) {
		leaf_direction = LEAF_STATIC;
		leaf_rotation = 0.0f;
	}

	//Animacion de Cometa
	kite_tail_move_time += (deltaTime * 0.001f) / 0.5f;
	if (kite_tail_move_time >= 0.5f) {
		kite_tail_move_time = 0.0f;
		kite_tail_rotation_offset_x += (rand() % kite_wind_strength) - (kite_wind_strength / 2.0f);
		if (kite_tail_rotation_offset_x > 7.0f) {
			kite_tail_rotation_offset_x = 7.0f;
		}
		if (kite_tail_rotation_offset_x < -7.0f) {
			kite_tail_rotation_offset_x = -7.0f;
		}
		kite_tail_rotation_offset_z += ((rand() % 600) / 100.0f) - 3.0f;
		if (kite_tail_rotation_offset_z > 7.0f) {
			kite_tail_rotation_offset_z = 7.0f;
		}
		if (kite_tail_rotation_offset_z < -7.0f) {
			kite_tail_rotation_offset_z = -7.0f;
		}
	}
	kite_wind_strength_change_time += (deltaTime * 0.001f) / 7.0f;
	if (kite_wind_strength_change_time >= 7.0f) {
		kite_wind_strength_change_time = 0.0f;
		if (kite_wind_strength >= 5) {
			kite_wind_change = -1;
		}
		if (kite_wind_strength <= 2) {
			kite_wind_change = 1;
		}
		kite_wind_strength += kite_wind_change;
	}

	// Animacion Columpio
	if (swing_direction == SWING_MOVE_FRONT) {
		swing_rotation += (deltaTime * 0.001f * swing_angle_limit) / 1.0f;
		if (swing_rotation >= swing_angle_limit) {
			swing_rotation = swing_angle_limit;
			swing_angle_change = true;
			swing_direction = SWING_MOVE_BACK;
		}
		if (swing_stopping == true && swing_rotation >= 0.0f) {
			swing_direction = SWING_STATIC;
		}
	}
	else if (swing_direction == SWING_MOVE_BACK) {
		swing_rotation -= (deltaTime * 0.001f * swing_angle_limit) / 1.0f;
		if (swing_rotation <= -1.0f * swing_angle_limit) {
			swing_rotation = -1.0f * swing_angle_limit;
			swing_angle_change = true;
			swing_direction = SWING_MOVE_FRONT;
		}
		if (swing_stopping == true && swing_rotation <= 0.0f) {
			swing_direction = SWING_STATIC;
		}
	}
	else if (swing_direction == SWING_STATIC) {
		swing_static_time += (deltaTime * 0.001f) / 4.0f;
		if (swing_static_time >= 1.0f) {
			swing_rotation = 0.0f;
			swing_direction = SWING_MOVE_FRONT;
			swing_movement = SWING_ACCELERATE;
			swing_angle_change = false;
			swing_stopping = false;
			swing_angle_limit = 5.0f;
			swing_static_time = 0.0f;
		}
	}
	if (swing_angle_change == true) {
		if (swing_movement == SWING_ACCELERATE) {
			swing_angle_limit += 5.0f;
			if (swing_angle_limit >= 45.0f) {
				swing_stopping = false;
				swing_movement = SWING_DEACCELERATE;
			}
		}
		else if (swing_movement == SWING_DEACCELERATE) {
			swing_angle_limit -= 5.0f;
			if (swing_angle_limit <= 0.0f) {
				swing_stopping = true;
				swing_angle_limit = 5.0f;
				swing_movement = swing_movement;
			}
		}
		swing_angle_change = false;
	}

	// Baby Yoda Animation
	baby_yoda_last_offset_y = baby_yoda_offset_y;
	if (baby_yoda_levitating) {
		if (baby_yoda_should_save_initial_values) {
			baby_yoda_initial_time = lastFrame;
			baby_yoda_initial_left_arm_rotate_y = baby_yoda_left_arm_rotate_y;
			baby_yoda_initial_left_arm_rotate_z = baby_yoda_left_arm_rotate_z;
			baby_yoda_initial_right_arm_rotate_y = baby_yoda_right_arm_rotate_y;
			baby_yoda_initial_right_arm_rotate_z = baby_yoda_right_arm_rotate_z;
			baby_yoda_initial_offset_y = baby_yoda_offset_y;
			baby_yoda_should_save_initial_values = false;
		}
		if (baby_yoda_levitation_stage == BABY_YODA_PREPARING_ARMS) {
			if (lastFrame - baby_yoda_initial_time < 1.0f * 1000.0f) {
				float percentage = (lastFrame - baby_yoda_initial_time) / (1.0f * 1000.0f);
				baby_yoda_left_arm_rotate_y = baby_yoda_initial_left_arm_rotate_y + (10.0f - baby_yoda_initial_left_arm_rotate_y) * percentage;
				baby_yoda_left_arm_rotate_z = baby_yoda_initial_left_arm_rotate_z + (0.0f - baby_yoda_initial_left_arm_rotate_z) * percentage;
				baby_yoda_right_arm_rotate_y = baby_yoda_initial_right_arm_rotate_y + (-10.0f - baby_yoda_initial_right_arm_rotate_y) * percentage;
				baby_yoda_right_arm_rotate_z = baby_yoda_initial_right_arm_rotate_z + (0.0f - baby_yoda_initial_right_arm_rotate_z) * percentage;
			}
			else {
				baby_yoda_left_arm_rotate_y = 10.0f;
				baby_yoda_left_arm_rotate_z = 5.0f;
				baby_yoda_right_arm_rotate_y = -10.0f;
				baby_yoda_right_arm_rotate_z = -5.0f;
				baby_yoda_levitation_stage = BABY_YODA_LOWERING_ARMS;
				baby_yoda_should_save_initial_values = true;
			}
		}
		else if (baby_yoda_levitation_stage == BABY_YODA_LOWERING_ARMS) {
			if (lastFrame - baby_yoda_initial_time < 2.5f * 1000.0f) {
				float percentage = (lastFrame - baby_yoda_initial_time) / (2.5f * 1000.0f);
				baby_yoda_left_arm_rotate_z = baby_yoda_initial_left_arm_rotate_z + (50.0f - baby_yoda_initial_left_arm_rotate_z) * percentage;
				baby_yoda_right_arm_rotate_z = baby_yoda_initial_right_arm_rotate_z + (-50.0f - baby_yoda_initial_right_arm_rotate_z) * percentage;
				baby_yoda_offset_y = baby_yoda_initial_offset_y + (1.5f - baby_yoda_initial_offset_y) * percentage;
			}
			else {
				baby_yoda_left_arm_rotate_z = 50.0f;
				baby_yoda_right_arm_rotate_z = -50.0f;
				baby_yoda_offset_y = 1.5f;
				baby_yoda_levitation_stage = BABY_YODA_FORWARD_ARMS;
				baby_yoda_should_save_initial_values = true;
			}
		}
		else if (baby_yoda_levitation_stage == BABY_YODA_FORWARD_ARMS) {
			if (lastFrame - baby_yoda_initial_time < 2.0f * 1000.0f) {
				float percentage = (lastFrame - baby_yoda_initial_time) / (2.0f * 1000.0f);
				baby_yoda_left_arm_rotate_y = baby_yoda_initial_left_arm_rotate_y + (25.0f - baby_yoda_initial_left_arm_rotate_y) * percentage;
				baby_yoda_right_arm_rotate_y = baby_yoda_initial_right_arm_rotate_y + (-25.0f - baby_yoda_initial_right_arm_rotate_y) * percentage;
			}
			else {
				baby_yoda_left_arm_rotate_y = 25.0f;
				baby_yoda_right_arm_rotate_y = -25.0f;
				baby_yoda_levitation_stage = BABY_YODA_WAVING_ARMS;
				baby_yoda_should_save_initial_values = true;
			}
		}
		else if (baby_yoda_levitation_stage == BABY_YODA_WAVING_ARMS) {
			float baby_yoda_arm_rotation_goal = baby_yoda_wave_direction == BABY_YODA_WAVE_UP ? 55.0f : 45.0f;
			float baby_yoda_offset_y_goal = baby_yoda_wave_direction == BABY_YODA_WAVE_UP ? 1.56f : 1.5f;
			if (lastFrame - baby_yoda_initial_time < 0.8f * 1000.0f) {
				float percentage = (lastFrame - baby_yoda_initial_time) / (0.8f * 1000.0f);
				baby_yoda_left_arm_rotate_z = baby_yoda_initial_left_arm_rotate_z + (baby_yoda_arm_rotation_goal - baby_yoda_initial_left_arm_rotate_z) * percentage;
				baby_yoda_right_arm_rotate_z = baby_yoda_initial_right_arm_rotate_z + (baby_yoda_arm_rotation_goal * -1.0f - baby_yoda_initial_right_arm_rotate_z) * percentage;
				baby_yoda_offset_y = baby_yoda_initial_offset_y + (baby_yoda_offset_y_goal - baby_yoda_initial_offset_y) * percentage;
			}
			else {
				baby_yoda_left_arm_rotate_z = baby_yoda_arm_rotation_goal;
				baby_yoda_right_arm_rotate_z = -1.0f * baby_yoda_arm_rotation_goal;
				baby_yoda_offset_y = baby_yoda_offset_y_goal;
				baby_yoda_wave_direction = baby_yoda_wave_direction == BABY_YODA_WAVE_UP ? BABY_YODA_WAVE_DOWN : BABY_YODA_WAVE_UP;
				baby_yoda_should_save_initial_values = true;
			}
		}
		else if (baby_yoda_levitation_stage == BABY_YODA_TO_NORMAL_ARMS) {
			if (lastFrame - baby_yoda_initial_time < 1.0f * 1000.0f) {
				float percentage = (lastFrame - baby_yoda_initial_time) / (1.0f * 1000.0f);
				baby_yoda_left_arm_rotate_y = baby_yoda_initial_left_arm_rotate_y + (20.0f - baby_yoda_initial_left_arm_rotate_y) * percentage;
				baby_yoda_left_arm_rotate_z = baby_yoda_initial_left_arm_rotate_z + (40.0f - baby_yoda_initial_left_arm_rotate_z) * percentage;
				baby_yoda_right_arm_rotate_y = baby_yoda_initial_right_arm_rotate_y + (-20.0f - baby_yoda_initial_right_arm_rotate_y) * percentage;
				baby_yoda_right_arm_rotate_z = baby_yoda_initial_right_arm_rotate_z + (-40.0f - baby_yoda_initial_right_arm_rotate_z) * percentage;
				baby_yoda_offset_y = baby_yoda_initial_offset_y + (0.0f - baby_yoda_initial_offset_y) * percentage;

			}
			else {
				baby_yoda_left_arm_rotate_y = 20.0f;
				baby_yoda_left_arm_rotate_z = 40.0f;
				baby_yoda_right_arm_rotate_y = -20.0f;
				baby_yoda_right_arm_rotate_z = -40.0f;
				baby_yoda_offset_y = 0.0f;
				baby_yoda_levitating = false;
			}
		}
	}
	baby_yoda_delta_offset_y = baby_yoda_offset_y - baby_yoda_last_offset_y;

	// Animacion Flotador
	if (pool_float_speed == 0.0f) {
		if (lastFrame - pool_float_move_time > 3.0f * 1000.0f) {
			pool_float_angle = (rand() % 360) * 1.0f;
			pool_float_speed = 0.5f;
		}
	}
	else if (pool_float_speed > 0.0f) {
		if (lastFrame - pool_float_move_time > 0.1f * 1000.0f) {
			pool_float_move_time = lastFrame;
			float pool_float_delta_x = sin(glm::radians(pool_float_angle)) * pool_float_speed;
			float pool_float_delta_z = cos(glm::radians(pool_float_angle)) * pool_float_speed;
			pool_float_offset_x += pool_float_delta_x;
			pool_float_offset_z += pool_float_delta_z;
			pool_float_speed -= 0.002f;
			if (pool_float_speed <= 0.0f) {
				pool_float_speed = 0.0f;
			}
			if (pool_float_offset_x > 8.4f || pool_float_offset_x < -8.4f) {
				pool_float_angle = pool_float_angle * -1.0f;
			}
			if (pool_float_offset_z > 3.8f || pool_float_offset_z < -3.8f) {
				pool_float_angle = (static_cast<int>(pool_float_angle + 180) % 360) * -1.0f;
			}
		}
	}

	// Animacion X Wing
	if (x_wing_should_save_initial_values) {
		x_wing_initial_time = lastFrame;
		x_wing_initial_rotate = x_wing_rotate;
		x_wing_should_save_initial_values = false;
	}
	if (x_wing_movement == X_WING_STRAIGHT_LINE) {
		float x_wing_delta_x = sin(glm::radians(x_wing_angle)) * (deltaTime * 1.0f / 5.0f);
		float x_wing_delta_z = cos(glm::radians(x_wing_angle)) * (deltaTime * 1.0f / 5.0f);
		x_wing_offset_x += x_wing_delta_x;
		x_wing_offset_z += x_wing_delta_z;
		if (glm::distance(glm::vec2(0.0f, 0.0f), glm::vec2(x_wing_offset_x, x_wing_offset_z)) > x_wing_movement_radius) {
			glm::vec2 vec = glm::normalize(glm::vec2(x_wing_offset_x, x_wing_offset_z)) * x_wing_movement_radius;
			x_wing_offset_x = vec.x;
			x_wing_offset_z = vec.y;
			x_wing_angle = static_cast<int>((rand() % 40) + x_wing_angle + 180.0f - 45.0f) % 360;
			x_wing_should_save_initial_values = true;
			x_wing_movement = X_WING_ROTATING;
		}
	}
	else if (x_wing_movement == X_WING_ROTATING) {
		if (lastFrame - x_wing_initial_time < 1.0f * 1000.0f) {
			float percentage = (lastFrame - x_wing_initial_time) / (1.0f * 1000.0f);
			x_wing_rotate = x_wing_initial_rotate + (x_wing_angle - x_wing_initial_rotate) * percentage;
		}
		else {
			x_wing_rotate = x_wing_angle;
			x_wing_movement = X_WING_STRAIGHT_LINE;
		}
	}

	//animacion fuego
	fire_rotation += 10.0f;
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
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	loadData();
	loadTextures();
	loadTextureDataBabyYoda();
	loadTextureDataMikeWazowski();
	loadTextureDataAang();
	loadAudio();

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader shaderStatic("shaders/shader_static.vs", "shaders/shader_static.fs");
	Shader shaderSkybox("shaders/shader_skybox.vs", "shaders/shader_skybox.fs");
	Shader shaderCube("shaders/shader_texture_color.vs", "shaders/shader_texture_color.fs");
	Shader shaderAnimate("shaders/shader_animate.vs", "shaders/shader_animate.fs");

	Torus torus(5.0f, 3.0f, 50, 50);

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
	Model Kite("resources/models/Kite/Kite.obj");
	Model Jeep("resources/models/Jeep/Jeep.obj");
	Model Slide("resources/models/Slide/Slide.obj");
	Model Sandbox("resources/models/Sandbox/Sandbox.obj");
	Model LamboWheel("resources/models/Lambo/Wheel.obj");
	Model LamboBody("resources/models/Lambo/Carroceria.obj");
	Model Subaru("resources/models/Subaru/Subaru.obj");
	Model LampSingle("resources/models/Lamp/LampSingle.obj");
	Model OakTree("resources/models/Trees/OakTree.obj");
	Model LodTree("resources/models/Trees/LodTree.obj");
	Model Grill("resources/models/Grill/BBQ.obj");
	Model PicnicTable("resources/models/PicnicTable/Table.obj");
	Model Speakers("resources/models/Speakers/Speakers.obj");
	Model Goal("resources/models/Goal/Goal.obj");
	Model SwingSeat("resources/models/SwingParts/SwingSeat.obj");
	Model SwingStructure("resources/models/SwingParts/SwingStructure.obj");
	Model Apartment("resources/models/Apartment/Building.obj");
	Model HouseThreeFloor("resources/models/HouseThreeFloor/HouseThree.obj");
	Model Fountain("resources/models/Fountain/Fountain.obj");
	Model GardenLight("resources/models/GardenLight/GardenLight.obj");
	Model Bush("resources/models/Bush/Bush.obj");
	Model Leaf("resources/models/Leaf/Leaf.obj");
	Model Platform("resources/models/DivingPlatform/Platform.obj");
	Model Xwing("resources/models/Xwing/Xwing.obj");
	Model testModel("resources/models/Grass/Grass.obj");
	Model TrashCan("resources/models/TrashCan/mitrashcan.obj");
	Model Scream("resources/models/Scream/Scream.obj");
	Model FireNation("resources/models/Fire_Nation_Frigate/FireNationFrigate.obj");
	Model Monster("resources/models/Sullivan/SullivanMonster.obj");
	ModelAnim KiteKid("resources/models/KiteKid/KiteKid.dae");
	KiteKid.initShaders(shaderAnimate.ID);

	// ARBOLES AREA VERDE

	vector<glm::vec3> bushPositions = {
		// ... primer columa
		glm::vec3(97.0f * scale, 0.25f, -65.0f * scale),  
		glm::vec3(84.0f * scale, 0.25f, -39.0f * scale),
		glm::vec3(77.0f * scale, 0.25f, -5.0f * scale),
		glm::vec3(62.0f * scale, 0.25f, -43.0f * scale),
		glm::vec3(57.0f * scale, 0.25f, -36.0f * scale),
		// ... segunda columa
		glm::vec3(90.0f * scale, 0.25f, -55.0f * scale),
		glm::vec3(52.0f * scale, 0.25f, -52.0f * scale),
		glm::vec3(90.0f * scale, 0.25f, -5.0f * scale),
		// ...tercera
		glm::vec3(75.0f * scale, 0.25f, -40.0f * scale),
		glm::vec3(72.0f * scale, 0.25f, -45.0f * scale),
		glm::vec3(75.0f * scale, 0.25f, -40.0f * scale),
		glm::vec3(72.0f * scale, 0.25f, -45.0f * scale),
		// ... cuarta
		glm::vec3(52.0f * scale, 0.25f, -34.0f * scale),
		glm::vec3(48.0f * scale, 0.25f, -35.0f * scale),
		glm::vec3(52.0f * scale, 0.25f, -32.0f * scale),
		glm::vec3(48.0f * scale, 0.25f, -35.0f * scale),
		// ... quinta
		glm::vec3(96.0f * scale, 0.25f, -23.0f * scale),
		glm::vec3(49.0f * scale, 0.25f, -25.0f * scale),
		glm::vec3(72.0f * scale, 0.25f, -21.0f * scale),
		glm::vec3(53.0f * scale, 0.25f, -25.0f * scale),
		// ... sexta
		glm::vec3(78.0f * scale, 0.25f, -12.0f * scale),
		glm::vec3(63.0f * scale, 0.25f, -10.0f * scale),
		glm::vec3(78.0f * scale, 0.25f, -5.0f * scale),
		glm::vec3(56.0f * scale, 0.25f, -6.0f * scale),
		// ... septima
		glm::vec3(84.0f * scale, 0.25f, 0.0f * scale),
		glm::vec3(72.0f * scale, 0.25f, 6.0f * scale),
		glm::vec3(75.0f * scale, 0.25f, 12.0f * scale),
		glm::vec3(51.0f * scale, 0.25f, 7.0f * scale),
		// ... octava
		glm::vec3(52.0f * scale, 0.25f, 18.0f * scale),
		glm::vec3(49.0f * scale, 0.25f, 20.0f * scale),
		glm::vec3(67.0f * scale, 0.25f, 26.0f * scale),
		glm::vec3(90.0f * scale, 0.25f, 21.0f * scale),
		// ... novena
		glm::vec3(97.0f * scale, 0.25f, 31.0f * scale),
		glm::vec3(51.0f * scale, 0.25f, 29.0f * scale),
		glm::vec3(97.0f * scale, 0.25f, 36.0f * scale),
		glm::vec3(49.0f * scale, 0.25f, 32.0f * scale),
		// ... decima
		glm::vec3(88.0f * scale, 0.25f, 4.0f * scale),
		glm::vec3(63.0f * scale, 0.25f, -18.0f * scale),
		glm::vec3(78.0f * scale, 0.25f, 23.0f * scale),
		glm::vec3(67.0f * scale, 0.25f, 15.0f * scale),
	};

	vector<glm::vec3> oakTreePositions = {
		// ... segunda columna
		glm::vec3(50.0f * scale, 1.0f, -63.0f * scale),
		glm::vec3(77.0f * scale, 1.0f, -65.0f * scale),
		glm::vec3(87.0f * scale, 1.0f, -63.0f * scale),
		glm::vec3(97.0f * scale, 1.0f, -65.0f * scale),
		// ... segunda columna
		glm::vec3(50.0f * scale, 0.25f, -63.0f * scale),
		glm::vec3(77.0f * scale, 1.0f, -52.0f * scale),
		glm::vec3(57.0f * scale, 1.0f, -55.0f * scale),
		glm::vec3(67.0f * scale, 1.0f, -53.0f * scale),
		// ... tercera
		glm::vec3(87.0f * scale, 1.0f, -45.0f * scale),
		glm::vec3(57.0f * scale, 1.0f, -44.0f * scale),
		glm::vec3(87.0f * scale, 1.0f, -45.0f * scale),
		glm::vec3(67.0f * scale, 1.0f, -47.0f * scale),
		// ... cuarta
		glm::vec3(77.0f * scale, 1.0f, -33.0f * scale),
		glm::vec3(57.0f * scale, 1.0f, -37.0f * scale),
		glm::vec3(63.0f * scale, 1.0f, -33.0f * scale),
		glm::vec3(72.0f * scale, 1.0f, -29.0f * scale),
		// ... quinta
		glm::vec3(87.0f * scale, 1.0f, -21.0f * scale),
		glm::vec3(67.0f * scale, 1.0f, -25.0f * scale),
		glm::vec3(52.0f * scale, 1.0f, -23.0f * scale),
		glm::vec3(67.0f * scale, 1.0f, -26.0f * scale),
		// ... sexta
		glm::vec3(76.0f * scale, 1.0f, -15.0f * scale),
		glm::vec3(97.0f * scale, 1.0f, -12.0f * scale),
		glm::vec3(56.0f * scale, 1.0f, -13.0f * scale),
		glm::vec3(76.0f * scale, 1.0f, -14.0f * scale),
		// ... septima
		glm::vec3(85.0f * scale, 0.25f, -10.0f * scale),
		glm::vec3(77.0f * scale, 1.0f, -9.0f * scale),
		glm::vec3(67.0f * scale, 1.0f, -7.0f * scale),
		// ... octava
		glm::vec3(87.0f * scale, 1.0f, 0.0f * scale),
		glm::vec3(57.0f * scale, 1.0f, 2.0f * scale),
		glm::vec3(87.0f * scale, 1.0f, -3.0f * scale),
		glm::vec3(67.0f * scale, 1.0f, -4.0f * scale),
		// ... novena
		glm::vec3(77.0f * scale, 1.0f, 12.0f * scale),
		glm::vec3(57.0f * scale, 1.0f, 10.0f * scale),
		glm::vec3(63.0f * scale, 1.0f, 4.0f * scale),
		glm::vec3(72.0f * scale, 1.0f, -3.0f * scale),
		// ... decima
		glm::vec3(85.0f * scale, 0.25f, 18.0f * scale),
		glm::vec3(77.0f * scale, 1.0f, 23.0f * scale),
		glm::vec3(67.0f * scale, 1.0f, 24.0f * scale),
		glm::vec3(57.0f * scale, 1.0f, 29.0f * scale),
		// ... onceava
		glm::vec3(87.0f * scale, 1.0f, 32.0f * scale),
		glm::vec3(57.0f * scale, 1.0f, 34.0f * scale),
		glm::vec3(87.0f * scale, 1.0f, 35.0f * scale),
		glm::vec3(67.0f * scale, 1.0f, 30.0f * scale),
		// ... doceava
		glm::vec3(77.0f * scale, 1.0f, 12.0f * scale),
		glm::vec3(57.0f * scale, 1.0f, 10.0f * scale),
		glm::vec3(63.0f * scale, 1.0f, 4.0f * scale),
		glm::vec3(72.0f * scale, 1.0f, -3.0f * scale),
	};

	vector<glm::vec3> lodTreePositions = {
		// ... primera  columna
		glm::vec3(85.0f * scale, 0.25f, -63.0f * scale),
		glm::vec3(77.0f * scale, 1.0f, -61.0f * scale),
		glm::vec3(87.0f * scale, 1.0f, -63.0f * scale),
		glm::vec3(56.0f * scale, 1.0f, -65.0f * scale),
		// ... segunda columna
		glm::vec3(60.0f * scale, 1.0f, -65.0f * scale),
		glm::vec3(87.0f * scale, 1.0f, -55.0f * scale),
		glm::vec3(56.0f * scale, 1.0f, -56.0f * scale),
		glm::vec3(49.0f * scale, 1.0f, -48.0f * scale),
		// ... tercera
		glm::vec3(80.0f * scale, 1.0f, -45.0f * scale),
		glm::vec3(57.0f * scale, 1.0f, -43.0f * scale),
		glm::vec3(77.0f * scale, 1.0f, -45.0f * scale),
		glm::vec3(50.0f * scale, 1.0f, -41.0f * scale),
		// ... cuerta
		glm::vec3(87.0f * scale, 1.0f, -33.0f * scale),
		glm::vec3(67.0f * scale, 1.0f, -35.0f * scale),
		glm::vec3(94.0f * scale, 1.0f, -32.0f * scale),
		glm::vec3(51.0f * scale, 1.0f, -35.0f * scale),
		// ... quinta
		glm::vec3(92.0f * scale, 1.0f, -25.0f * scale),
		glm::vec3(63.0f * scale, 1.0f, -22.0f * scale),
		glm::vec3(75.0f * scale, 1.0f, -25.0f * scale),
		glm::vec3(57.0f * scale, 1.0f, -21.0f * scale),
		// ... sexta
		glm::vec3(49.0f * scale, 1.0f, -12.0f * scale),
		glm::vec3(67.0f * scale, 1.0f, -15.0f * scale),
		glm::vec3(80.0f * scale, 1.0f, -15.0f * scale),
		glm::vec3(78.0f * scale, 1.0f, -14.0f * scale),
		// ... septima
		glm::vec3(60.0f * scale, 1.0f, -5.0f * scale),
		glm::vec3(87.0f * scale, 1.0f, -7.0f * scale),
		glm::vec3(56.0f * scale, 1.0f, -8.0f * scale),
		// ... octava
		glm::vec3(80.0f * scale, 1.0f, -5.0f * scale),
		glm::vec3(57.0f * scale, 1.0f, 0.0f * scale),
		glm::vec3(77.0f * scale, 1.0f, 7.0f * scale),
		glm::vec3(50.0f * scale, 1.0f, 4.0f * scale),
		// ... novena
		glm::vec3(87.0f * scale, 1.0f, 16.0f * scale),
		glm::vec3(67.0f * scale, 1.0f, 18.0f * scale),
		glm::vec3(94.0f * scale, 1.0f, 14.0f * scale),
		glm::vec3(51.0f * scale, 1.0f, 23.0f * scale),
		// ... decima
		glm::vec3(60.0f * scale, 1.0f, 26.0f * scale),
		glm::vec3(87.0f * scale, 1.0f, 24.0f * scale),
		glm::vec3(56.0f * scale, 1.0f, 20.0f * scale),
		glm::vec3(94.0f * scale, 1.0f, 29.0f * scale),
		// ... onceava
		glm::vec3(80.0f * scale, 1.0f, 34.0f * scale),
		glm::vec3(57.0f * scale, 1.0f, 31.0f * scale),
		glm::vec3(77.0f * scale, 1.0f, 35.0f * scale),
		glm::vec3(50.0f * scale, 1.0f, 37.0f * scale),
		// ... doceava
		glm::vec3(87.0f * scale, 1.0f, 14.0f * scale),
		glm::vec3(67.0f * scale, 1.0f, 16.0f * scale),
		glm::vec3(94.0f * scale, 1.0f, 10.0f * scale),
		glm::vec3(51.0f * scale, 1.0f, 12.0f * scale),
	};

	vector<glm::vec3> bushPositionsComun = {
		glm::vec3(3.0f * scale, 0.25f, -9.0f * scale),
		glm::vec3(3.0f * scale, 0.25f, -15.0f * scale),
		glm::vec3(3.0f * scale, 0.25f, -20.0f * scale),
		glm::vec3(3.0f * scale, 0.25f, -25.0f * scale),
		glm::vec3(3.0f * scale, 0.25f, -30.0f * scale),
		glm::vec3(3.0f * scale, 0.25f, -35.0f * scale),
		glm::vec3(3.0f * scale, 0.25f, -41.0f * scale),
		glm::vec3(3.0f * scale, 0.25f, -41.0f * scale),
		glm::vec3(8.0f * scale, 0.25f, -41.0f * scale),
		glm::vec3(13.0f * scale, 0.25f, -41.0f * scale),
		glm::vec3(18.0f * scale, 0.25f, -41.0f * scale),
		glm::vec3(23.0f * scale, 0.25f, -41.0f * scale),
		glm::vec3(28.0f * scale, 0.25f, -41.0f * scale),
		glm::vec3(-3.0f * scale, 0.25f, -9.0f * scale),
		glm::vec3(-3.0f * scale, 0.25f, -22.0f * scale),
		glm::vec3(-3.0f * scale, 0.25f, -27.0f * scale),
		glm::vec3(-3.0f * scale, 0.25f, -32.0f * scale),
		glm::vec3(-3.0f * scale, 0.25f, -37.0f * scale),
		glm::vec3(-3.0f * scale, 0.25f, -42.0f * scale),
		glm::vec3(-3.0f * scale, 0.25f, -48.0f * scale),
		glm::vec3(-3.0f * scale, 0.25f, -48.0f * scale),
		glm::vec3(2.0f * scale, 0.25f, -48.0f * scale),
		glm::vec3(7.0f * scale, 0.25f, -48.0f * scale),
		glm::vec3(12.0f * scale, 0.25f, -48.0f * scale),
		glm::vec3(17.0f * scale, 0.25f, -48.0f * scale),
		glm::vec3(22.0f * scale, 0.25f, -48.0f * scale),
		glm::vec3(28.0f * scale, 0.25f, -48.0f * scale),
	};

	vector<glm::vec3> oakTreePositionsComun = {
		glm::vec3(-27.0f * scale, 1.0f, -27.0f * scale),
		glm::vec3(-7.0f * scale, 1.0f, -27.0f * scale),
		glm::vec3(5.0f * scale, 1.0f, -27.0f * scale),
		glm::vec3(28.0f * scale, 1.0f, -27.0f * scale),
		glm::vec3(-26.0f * scale, 1.0f, -42.0f * scale),
		glm::vec3(-8.0f * scale, 1.0f, -42.0f * scale),
		glm::vec3(-26.0f * scale, 1.0f, -62.0f * scale),
		glm::vec3(-8.0f * scale, 1.0f, -62.0f * scale),
		glm::vec3(14.0f * scale, 1.0f, -62.0f * scale),
		glm::vec3(3.0f * scale, 1.0f, -52.0f * scale),
	};

	vector<glm::vec3> lodTreePositionsComun = {
		glm::vec3(-29.0f * scale, 0.25f, -9.0f * scale),
		glm::vec3(29.0f * scale, 0.25f, -9.0f * scale),
		glm::vec3(17.0f * scale, 1.0f, -27.0f * scale),
		glm::vec3(-17.0f * scale, 1.0f, -32.0f * scale),
		glm::vec3(-16.0f * scale, 1.0f, -52.0f * scale),
		glm::vec3(16.0f * scale, 1.0f, -52.0f * scale),
		glm::vec3(26.0f * scale, 1.0f, -52.0f * scale),
	};

	glm::mat4 modelBabyYodaBody;
	glm::mat4 modelBabyYodaArms;
	glm::mat4 modelMikeWazowski;
	glm::mat4 modelAang;
	glm::mat4 modelAangLeftLeg;
	glm::mat4 modelAangRightLeg;
	glm::vec3 aang_position = glm::vec3(10.0f * scale, 3.0f * scale, 10.0f * scale);

	load_song_with_index(0);
	alSourcePlay(sources[1]);
	alSourcePlay(sources[2]);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window)) {

		shaderSkybox.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// run animations
		// --------------
		runAnimations();

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

		// Faros de Luz Calle 1 Izquierda
		for (int i = 0; i <= 2; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3((21.6666f - 21.1666f * i) * scale, 0.0f, 0.5f * scale));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.1111f * scale));
			shaderStatic.setMat4("model", model);
			LampSingle.Draw(shaderStatic);
		}

		// Faros de Luz Calle 1 Izquierda
		for (int i = 0; i <= 3; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3((31.75f - 21.1666f * i) * scale, 0.0f, -8.0f * scale));
			model = glm::scale(model, glm::vec3(0.1111f * scale));
			shaderStatic.setMat4("model", model);
			LampSingle.Draw(shaderStatic);
		}

		// Faros de Luz Calle 2 Izquierda
		for (int j = 0; j <= 6; j++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.32f * scale, 0.0f, (37.071f - 13.34725 * j) * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.1111 * scale));
			shaderStatic.setMat4("model", model);
			LampSingle.Draw(shaderStatic);
		}

		// Faros de Luz Calle 3 Izquierda
		for (int j = 0; j <= 6; j++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(47.17f * scale, 0.0f, (37.071f - 13.34725 * j) * scale));
			model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.1111 * scale));
			shaderStatic.setMat4("model", model);
			LampSingle.Draw(shaderStatic);
		}

		// Iluminacion de Faros Calle 1 
		for (int j = 0; j <= 6; j++) {
			shaderStatic.setVec3("pointLight[" + std::to_string(j + 1) + "].position", glm::vec3((31.75f - 10.5833f * j) * scale, 3.0f * scale, -3.5f * scale));
			shaderStatic.setVec3("pointLight[" + std::to_string(j + 1) + "].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
			shaderStatic.setVec3("pointLight[" + std::to_string(j + 1) + "].diffuse", glm::vec3(1.0f, 0.9372f, 0.2588f));
			shaderStatic.setVec3("pointLight[" + std::to_string(j + 1) + "].specular", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderStatic.setFloat("pointLight[" + std::to_string(j + 1) + "].constant", 1.0f);
			shaderStatic.setFloat("pointLight[" + std::to_string(j + 1) + "].linear", 0.03f);
			shaderStatic.setFloat("pointLight[" + std::to_string(j + 1) + "].quadratic", 0.00032f);
		}

		// Iluminacion de Faros Calle 2
		for (int j = 0; j <= 6; j++) {
			shaderStatic.setVec3("pointLight[" + std::to_string(j + 8) + "].position", glm::vec3(-36.82f * scale, 3.0 * scale, (37.071f - 13.34725 * j) * scale));
			shaderStatic.setVec3("pointLight[" + std::to_string(j + 8) + "].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
			shaderStatic.setVec3("pointLight[" + std::to_string(j + 8) + "].diffuse", glm::vec3(1.0f, 0.9372f, 0.2588f));
			shaderStatic.setVec3("pointLight[" + std::to_string(j + 8) + "].specular", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderStatic.setFloat("pointLight[" + std::to_string(j + 8) + "].constant", 1.0f);
			shaderStatic.setFloat("pointLight[" + std::to_string(j + 8) + "].linear", 0.03f);
			shaderStatic.setFloat("pointLight[" + std::to_string(j + 8) + "].quadratic", 0.001f);
		}

		// Iluminacion de Faros Calle 3
		for (int j = 0; j <= 6; j++) {
			shaderStatic.setVec3("pointLight[" +  std::to_string(j + 15) + "].position", glm::vec3(43.67f * scale, 3.0 * scale, (37.071f - 13.34725 * j) * scale));
			shaderStatic.setVec3("pointLight[" + std::to_string(j + 15) + "].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
			shaderStatic.setVec3("pointLight[" + std::to_string(j + 15) + "].diffuse", glm::vec3(1.0f, 0.9372f, 0.2588f));
			shaderStatic.setVec3("pointLight[" + std::to_string(j + 15) + "].specular", glm::vec3(0.0f, 0.0f, 0.0f));
			shaderStatic.setFloat("pointLight[" + std::to_string(j + 15) + "].constant", 1.0f);
			shaderStatic.setFloat("pointLight[" + std::to_string(j + 15) + "].linear", 0.03f);
			shaderStatic.setFloat("pointLight[" + std::to_string(j + 15) + "].quadratic", 0.001f);
		}

		// Auto Jeep Calle 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(9.75f * scale, 0.35f, -1.75f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f * scale));
		shaderStatic.setMat4("model", model);
		Jeep.Draw(shaderStatic);

		// Auto Lambo Calle 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-17.75f * scale, 0.5f, -5.75f * scale));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.008333f * scale));
		shaderStatic.setMat4("model", model);
		LamboBody.Draw(shaderStatic);

		// Llantas Auto Lambo Calle 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-18.82f * scale, 2.95f, -6.45f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.008333f * scale));
		shaderStatic.setMat4("model", model);
		LamboWheel.Draw(shaderStatic);

		// Llantas Auto Lambo Calle 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-16.53f * scale, 2.95f, -6.45f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.008333f * scale));
		shaderStatic.setMat4("model", model);
		LamboWheel.Draw(shaderStatic);

		// Llantas Auto Lambo Calle 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-18.82f * scale, 2.95f, -5.05f * scale));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.008333f * scale));
		shaderStatic.setMat4("model", model);
		LamboWheel.Draw(shaderStatic);

		// Llantas Auto Lambo Calle 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-16.53f * scale, 2.95f, -5.05f * scale));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.008333f * scale));
		shaderStatic.setMat4("model", model);
		LamboWheel.Draw(shaderStatic);

		// Auto Subaru 2 Calle 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(43.9f * scale, 0.5f, 18.5f * scale));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.35f * scale));
		shaderStatic.setMat4("model", model);
		Subaru.Draw(shaderStatic);

		// Auto Jeep Calle 3
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-37.82f * scale, 0.35f, -25.75f * scale));
		model = glm::scale(model, glm::vec3(1.0f * scale));
		shaderStatic.setMat4("model", model);
		Jeep.Draw(shaderStatic);

		// Auto Subaru Calle 3
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-34.02f * scale, 0.35f, 22.75f * scale));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.35f * scale));
		shaderStatic.setMat4("model", model);
		Subaru.Draw(shaderStatic);

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
		model = glm::scale(model, glm::vec3(1.0f / 300.0f * 18.93f * scale, 1.0f / 300.0f * 17.0f * scale, 1.0f / 300.0f * 18.93f * scale));
		shaderStatic.setMat4("model", model);
		Grass.Draw(shaderStatic);

		// Columpio 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-84.045f * scale, 1.7f, 27.0f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.012f * scale));
		shaderStatic.setMat4("model", model);
		Swing.Draw(shaderStatic);

		// Columpio 2 sin columpio de en medio
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-84.045f * scale, 1.7f, 21.5f * scale));
		model = glm::scale(model, glm::vec3(0.012f * scale));
		shaderStatic.setMat4("model", model);
		SwingStructure.Draw(shaderStatic);

		// Columpio 2 Solo asiento
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-84.045f * scale, 2.855f * scale, 21.26f * scale));
		model = glm::rotate(model, glm::radians(swing_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.012f * scale));
		shaderStatic.setMat4("model", model);
		SwingSeat.Draw(shaderStatic);

		//Resbaladilla 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-75.045f * scale, 1.7f, 28.0f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.007f * scale));
		shaderStatic.setMat4("model", model);
		Slide.Draw(shaderStatic);

		//Resbaladilla 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-80.045f * scale, 1.7f, 28.0f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.007f * scale));
		shaderStatic.setMat4("model", model);
		Slide.Draw(shaderStatic);

		//Resbaladilla 3
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-50.0f * scale, 5.0f, 6.0f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.007f * scale));
		shaderStatic.setMat4("model", model);
		Slide.Draw(shaderStatic);

		//Caja de arena
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-78.045f * scale, 1.0f, 22.0f * scale));
		model = glm::scale(model, glm::vec3(0.002f * scale));
		shaderStatic.setMat4("model", model);
		Sandbox.Draw(shaderStatic);

		// X Wing
		model = glm::translate(glm::mat4(1.0f), x_wing_position);
		model = glm::translate(model, glm::vec3(x_wing_offset_x, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, x_wing_offset_z));
		model = glm::rotate(model, glm::radians(x_wing_rotate), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.02 * scale));
		shaderStatic.setMat4("model", model);
		Xwing.Draw(shaderStatic);

		//Arbol 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-60.0f * scale, 5.0f, 3.34f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(2.0f * scale));
		shaderStatic.setMat4("model", model);
		OakTree.Draw(shaderStatic);

		//Arbol 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-57.0f * scale, 5.0f, -2.0f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f * scale));
		shaderStatic.setMat4("model", model);
		OakTree.Draw(shaderStatic);


		// Hoja de Arbol 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3((-58.0f + leaf_offset_x) * scale, (5.67f + leaf_offset_y) * scale, (4.25f + leaf_offset_z) * scale));
		model = glm::rotate(model, glm::radians(leaf_rotation), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 0.666f * scale));
		shaderStatic.setMat4("model", model);
		Leaf.Draw(shaderStatic);

		// Hoja de Arbol 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3((-54.25f + leaf_offset_x) * scale, (5.67f + leaf_offset_y) * scale, (-2.75f + leaf_offset_z * -1) * scale));
		model = glm::rotate(model, glm::radians(leaf_rotation), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 0.666f * scale));
		shaderStatic.setMat4("model", model);
		Leaf.Draw(shaderStatic);

		// Banca 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-58.0f * scale, 5.0f, 1.0f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.0125f * scale));
		shaderStatic.setMat4("model", model);
		Banca.Draw(shaderStatic);

		// Banca 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-76.045f * scale, 1.0f, 17.0f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0125f * scale));
		shaderStatic.setMat4("model", model);
		Banca.Draw(shaderStatic);

		// Banca 3
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

		// Hilo de Cometa
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-57.725f * scale, 2.08f * scale, 1.205f * scale));
		model = glm::rotate(model, glm::radians(50.0f + kite_tail_rotation_offset_x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(70.0f + kite_tail_rotation_offset_z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f * scale, 0.8f * scale, 0.2f * scale));
		shaderStatic.setMat4("model", model);
		Kite.Draw(shaderStatic);

		//TrashCan Monsters Inc

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-84.045f * scale, 5.0f, 17.5f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f * scale));
		shaderStatic.setMat4("model", model);
		TrashCan.Draw(shaderStatic);

		/* AREA RESIDENCIAL */

		// Piso de Pasto
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 10; j++) {
				model = glm::translate(glm::mat4(1.0f), glm::vec3((-28.35f + 6.3f * i) * scale, -0.1f, (4.284f + 6.568f * j) * scale));
				model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 6.3f * scale, 1.0f, 1.0f / 5000.0f * 6.568f * scale));
				shaderStatic.setMat4("model", model);
				Greens.Draw(shaderStatic);
			}
		}

		//Arbol 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-7.5f * scale, 1.0f, (14.0f - 2.0f) * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.25f * scale));
		shaderStatic.setMat4("model", model);
		OakTree.Draw(shaderStatic);

		//Arbol 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(7.5f * scale, 1.0f, (14.0f - 2.0f) * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.25f * scale));
		shaderStatic.setMat4("model", model);
		OakTree.Draw(shaderStatic);

		//Arbol 3
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-7.5f * scale, 1.0f, 28.5f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.25f * scale));
		shaderStatic.setMat4("model", model);
		OakTree.Draw(shaderStatic);

		//Arbol 4
		model = glm::translate(glm::mat4(1.0f), glm::vec3(7.5f * scale, 1.0f, 28.5f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.25f * scale));
		shaderStatic.setMat4("model", model);
		OakTree.Draw(shaderStatic);

		// Apartamentos 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-29.35f * scale, 0.1f, 38.35f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 3200.0f * 30.0f * scale));
		shaderStatic.setMat4("model", model);
		Apartment.Draw(shaderStatic);

		// Apartamentos 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(29.35f * scale, 0.1f, 4.0f * scale));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f / 3200.0f * 30.0f * scale));
		shaderStatic.setMat4("model", model);
		Apartment.Draw(shaderStatic);

		// Casa 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-7.35f * scale, 0.1f, 45.0f * scale));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f / 430.0f * 12.5f * scale));
		shaderStatic.setMat4("model", model);
		HouseThreeFloor.Draw(shaderStatic);

		// Casa 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(10.65f * scale, 0.1f, 45.0f * scale));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f / 430.0f * 12.5f * scale));
		shaderStatic.setMat4("model", model);
		HouseThreeFloor.Draw(shaderStatic);

		// Fuente 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f * scale, 0.1f, 21.2f * scale));
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f / 1317.5f * 10.0f * scale, 1.0f / 1907.5f * 10.0f * scale, 1.0f / 1907.5f * 10.0f * scale));
		shaderStatic.setMat4("model", model);
		Fountain.Draw(shaderStatic);

		// Camino 1
		for (int i = 0; i <= 1; i++) {
			for (int j = 0; j <= 24; j++) {
				model = glm::translate(glm::mat4(1.0f), glm::vec3((-0.75f + 1.5f * i) * scale, 0.0f, (1.662f + 1.324f * j) * scale));
				model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 1.5f * scale, 1.0f, 1.0f / 5000.0f * 1.324f * scale));
				shaderStatic.setMat4("model", model);
				Path.Draw(shaderStatic);
			}
		}

		// Camino 2
		for (int i = 0; i <= 1; i++) {
			for (int j = 0; j <= 32; j++) {
				model = glm::translate(glm::mat4(1.0f), glm::vec3((-21.184f + 1.324f * j) * scale, 0.0f, (21.87f - 1.5f * i) * scale));
				model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 1.5f * scale, 1.0f, 1.0f / 5000.0f * 1.324f * scale));
				shaderStatic.setMat4("model", model);
				Path.Draw(shaderStatic);
			}
		}

		// Faros de Luz Derecha Camino 1
		for (int i = 0; i <= 2; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.22f * scale, 0.1f, (0.75f + 5.5833f * i) * scale));
			model = glm::scale(model, glm::vec3(0.2777f * scale));
			shaderStatic.setMat4("model", model);
			GardenLight.Draw(shaderStatic);
		}

		// Faros de Luz Izquierda Camino 1
		for (int i = 0; i <= 2; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(3.38f * scale, 0.1f, (0.75f + 5.5833f * i) * scale));
			model = glm::scale(model, glm::vec3(0.2777f * scale));
			shaderStatic.setMat4("model", model);
			GardenLight.Draw(shaderStatic);
		}

		// Faros de Luz Derecha Camino 1
		for (int i = 0; i <= 1; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.22f * scale, 0.1f, (23.5f + 5.5833f * i) * scale));
			model = glm::scale(model, glm::vec3(0.2777f * scale));
			shaderStatic.setMat4("model", model);
			GardenLight.Draw(shaderStatic);
		}

		// Faros de Luz Izquierda Camino 1
		for (int i = 0; i <= 1; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3(3.38f * scale, 0.1f, (23.5f + 5.5833f * i) * scale));
			model = glm::scale(model, glm::vec3(0.2777f * scale));
			shaderStatic.setMat4("model", model);
			GardenLight.Draw(shaderStatic);
		}

		// Faros de Luz Derecha Camino 2
		for (int i = 0; i <= 1; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3((-17.85f + 5.5833f * i) * scale, 0.0f, 20.9f * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.2777f * scale));
			shaderStatic.setMat4("model", model);
			GardenLight.Draw(shaderStatic);
		}

		// Faros de Luz Izquierda Camino 2
		for (int i = 0; i <= 1; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3((-17.85f + 5.5833f * i) * scale, 0.0f, 17.74f * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.2777f * scale));
			shaderStatic.setMat4("model", model);
			GardenLight.Draw(shaderStatic);
		}

		// Faros de Luz Derecha Camino 2
		for (int i = 0; i <= 1; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3((6.15f + 5.5833f * i) * scale, 0.0f, 20.9f * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.2777f * scale));
			shaderStatic.setMat4("model", model);
			GardenLight.Draw(shaderStatic);
		}

		// Faros de Luz Izquierda Camino 2
		for (int i = 0; i <= 1; i++) {
			model = glm::translate(glm::mat4(1.0f), glm::vec3((6.15f + 5.5833f * i) * scale, 0.0f, 17.74f * scale));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.2777f * scale));
			shaderStatic.setMat4("model", model);
			GardenLight.Draw(shaderStatic);
		}

		/* AREA COMUN */

		//Arboles

		// Arbustos
		for (glm::vec3 bushPositionComun : bushPositionsComun) {
			model = glm::translate(glm::mat4(1.0f), bushPositionComun);
			model = glm::scale(model, glm::vec3(0.5666f * scale));
			shaderStatic.setMat4("model", model);
			Bush.Draw(shaderStatic);
		}

		//Arboles Oak
		for (glm::vec3 oakTreePosition : oakTreePositionsComun) {
			model = glm::translate(glm::mat4(1.0f), oakTreePosition);
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(1.666f * scale));
			shaderStatic.setMat4("model", model);
			OakTree.Draw(shaderStatic);
		}

		// Arboles Lod
		for (glm::vec3 lodTreePositionComun : lodTreePositionsComun) {
			model = glm::translate(glm::mat4(1.0f), lodTreePositionComun);
			model = glm::scale(model, glm::vec3(1.0f * scale));
			shaderStatic.setMat4("model", model);
			LodTree.Draw(shaderStatic);
		}

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
		model = glm::scale(model, glm::vec3(1.0f / 92.5f * 20.0f * scale, 1.0f / 97.0f * 10.0f * scale, 1.0f / 52.0f * 10.0f  *  scale));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		Pool.Draw(shaderStatic);

		// Plataforma de Clavados
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-27.0f * scale, 2.25f, -17.45f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 100.0f * 5.0f * scale, 1.0f / 5.0f * 0.05f * scale, 1.0f / 20.0f * 0.9f * scale));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		Platform.Draw(shaderStatic);

		//Mesa Picnic Bocinas
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-17.20f * scale, 0.0f, -25.45f * scale));
		model = glm::scale(model, glm::vec3(0.0013f * scale));
		shaderStatic.setMat4("model", model);
		PicnicTable.Draw(shaderStatic);

		// Bocina 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-16.80f * scale, 1.1f * scale, -25.60f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f * scale));
		shaderStatic.setMat4("model", model);
		Speakers.Draw(shaderStatic);

		// Bocina 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-17.80f * scale, 1.1f * scale, -25.60f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f * scale));
		shaderStatic.setMat4("model", model);
		Speakers.Draw(shaderStatic);

		//Parrilla 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(9.0f * scale, 1.0f, -37.0f * scale));
		model = glm::scale(model, glm::vec3(0.01f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		Grill.Draw(shaderStatic);

		//Parrilla 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(17.0f * scale, 1.0f, -37.0f * scale));
		model = glm::scale(model, glm::vec3(0.01f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		Grill.Draw(shaderStatic);

		//Parrilla 3
		model = glm::translate(glm::mat4(1.0f), glm::vec3(25.0f * scale, 1.0f, -37.0f * scale));
		model = glm::scale(model, glm::vec3(0.01f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		Grill.Draw(shaderStatic);

		//Parrilla 4
		model = glm::translate(glm::mat4(1.0f), glm::vec3(13.0f * scale, 1.0f, -21.0f * scale));
		model = glm::scale(model, glm::vec3(0.01f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		shaderStatic.setMat4("model", model);
		Grill.Draw(shaderStatic);

		//Parrilla 5
		model = glm::translate(glm::mat4(1.0f), glm::vec3(21.0f * scale, 1.0f, -21.0f * scale));
		model = glm::scale(model, glm::vec3(0.01f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		shaderStatic.setMat4("model", model);
		Grill.Draw(shaderStatic);

		//Mesa Picnic 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(9.0f * scale, 1.0f, -33.0f * scale));
		model = glm::scale(model, glm::vec3(0.0013f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		PicnicTable.Draw(shaderStatic);

		//Mesa Picnic 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(17.0f * scale, 1.0f, -33.0f * scale));
		model = glm::scale(model, glm::vec3(0.0013f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		PicnicTable.Draw(shaderStatic);

		//Mesa Picnic 3
		model = glm::translate(glm::mat4(1.0f), glm::vec3(25.0f * scale, 1.0f, -33.0f * scale));
		model = glm::scale(model, glm::vec3(0.0013f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		PicnicTable.Draw(shaderStatic);

		//Mesa Picnic 4
		model = glm::translate(glm::mat4(1.0f), glm::vec3(13.0f * scale, 1.0f, -24.0f * scale));
		model = glm::scale(model, glm::vec3(0.0013f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		PicnicTable.Draw(shaderStatic);

		//Mesa Picnic 5
		model = glm::translate(glm::mat4(1.0f), glm::vec3(21.0f * scale, 1.0f, -24.0f * scale));
		model = glm::scale(model, glm::vec3(0.0013f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		PicnicTable.Draw(shaderStatic);

		//Porteria 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(9.0f * scale, 1.0f, -15.0f * scale));
		model = glm::scale(model, glm::vec3(0.8f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		Goal.Draw(shaderStatic);

		//Porteria 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(25.0f * scale, 1.0f, -15.0f * scale));
		model = glm::scale(model, glm::vec3(0.8f * scale));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		Goal.Draw(shaderStatic);

		// Agua de Alberca
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-17.20f * scale, 0.85f, -16.45f * scale));
		model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 19.0f * scale, 1.0f, 1.0f / 5000.0f * 9.0f * scale));
		shaderStatic.setMat4("model", model);
		Water.Draw(shaderStatic);

		//Fragata Nacion del Fuego
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-17.20f * scale, 0.0f, -16.45f * scale));
		model = glm::scale(model, glm::vec3( 0.0005f * scale));
		shaderStatic.setMat4("model", model);
		FireNation.Draw(shaderStatic);

		//TrashCan Monsters Inc 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-12.80f * scale, 5.0f, -25.60f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderStatic.setMat4("model", model);
		TrashCan.Draw(shaderStatic);

		//TrashCan Monsters Inc 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(4.80f * scale, 5.0f, -32.60f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f * scale));
		shaderStatic.setMat4("model", model);
		TrashCan.Draw(shaderStatic);


		//TrashCan Monsters Inc 3
		model = glm::translate(glm::mat4(1.0f), glm::vec3(4.80f * scale, 5.0f, -21.60f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f * scale));
		shaderStatic.setMat4("model", model);
		TrashCan.Draw(shaderStatic);

		//Scream 1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(13.0f * scale, 1.0f * scale, -24.65f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f * scale));
		shaderStatic.setMat4("model", model);
		Scream.Draw(shaderStatic);

		//Scream 2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(25.0f * scale, 1.0f, -13.5f * scale));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.15f * scale));
		shaderStatic.setMat4("model", model);
		Scream.Draw(shaderStatic);

		//MonsterSullivan
		model = glm::translate(glm::mat4(1.0f), glm::vec3(9.5f * scale, 1.0f, -15.0f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.007f * scale));
		shaderStatic.setMat4("model", model);
		Monster.Draw(shaderStatic);




		/* AREA VERDE */

		// Piso de Pasto
		for (int i = 0; i <= 7; i++) {
			for (int j = 0; j <= 15; j++) {
				model = glm::translate(glm::mat4(1.0f), glm::vec3((50.82f + 6.3f * i) * scale, -0.1f, (37.071f - 6.673625f * j) * scale));
				model = glm::scale(model, glm::vec3(1.0f / 5000.0f * 6.3f * scale, 1.0f, 1.0f / 5000.0f * 6.673625f * scale));
				shaderStatic.setMat4("model", model);
				Greens.Draw(shaderStatic);
			}
		}

		// Arbustos
		for (glm::vec3 bushPosition : bushPositions) {
			model = glm::translate(glm::mat4(1.0f), bushPosition);
			model = glm::scale(model, glm::vec3(0.5666f * scale));
			shaderStatic.setMat4("model", model);
			Bush.Draw(shaderStatic);
		}

		//Arboles Oak
		for (glm::vec3 oakTreePosition : oakTreePositions) {
			model = glm::translate(glm::mat4(1.0f), oakTreePosition);
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(1.666f * scale));
			shaderStatic.setMat4("model", model);
			OakTree.Draw(shaderStatic);
		}

		// Arboles Lod
		for (glm::vec3 lodTreePosition : lodTreePositions) {
			model = glm::translate(glm::mat4(1.0f), lodTreePosition);
			model = glm::scale(model, glm::vec3(1.0f * scale));
			shaderStatic.setMat4("model", model);
			LodTree.Draw(shaderStatic);
		}

		/* FIN DE AREAS */

		// Modelo de Prueba
		model = glm::translate(glm::mat4(1.0f), glm::vec3(lightPosition.x, lightPosition.y - 20.0f, lightPosition.z));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f / 300.0f * 50.0f, 1.0f / 300.0f * 50.0f, 1.0f / 100.0f));
		shaderStatic.setMat4("model", model);
		testModel.Draw(shaderStatic);


		//Luz aang
		shaderStatic.setVec3("pointLight[22].position", aang_position);
		shaderStatic.setVec3("pointLight[22].ambient", glm::vec3(0.3f, 0.1f, 0.1f));
		shaderStatic.setVec3("pointLight[22].diffuse", glm::vec3(1.0f, 0.2f, 0.0f));
		shaderStatic.setVec3("pointLight[22].specular", glm::vec3(0.1f, 0.0f, 0.0f));
		shaderStatic.setFloat("pointLight[22].constant", 1.0f);
		shaderStatic.setFloat("pointLight[22].linear", 0.03f);
		shaderStatic.setFloat("pointLight[22].quadratic", 0.00032f);


		/* MODELOS ANIMADOS */

		//// Light
		glm::vec3 lightColor = glm::vec3(0.6f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);

		shaderAnimate.use();
		shaderAnimate.setMat4("projection", projection);
		shaderAnimate.setMat4("view", view);

		shaderAnimate.setVec3("material.specular", glm::vec3(0.5f));
		shaderAnimate.setFloat("material.shininess", 32.0f);
		shaderAnimate.setVec3("light.ambient", ambientColor);
		shaderAnimate.setVec3("light.diffuse", diffuseColor);
		shaderAnimate.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		shaderAnimate.setVec3("light.direction", lightDirection);
		shaderAnimate.setVec3("viewPos", camera.Position);

		// Nino del Cometa
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-57.6f * scale, 0.7f * scale, 1.4f * scale));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f / 145.0f * 1.65f * scale));
		shaderAnimate.setMat4("model", model);
		KiteKid.Draw(shaderAnimate);

		shaderCube.use();

		// view/projection transformations
		shaderCube.setMat4("projection", projection);
		shaderCube.setMat4("view", view);

		// Ruler Cube
		/*model = glm::translate(glm::mat4(1.0f), glm::vec3(rulerPositionX, rulerPositionY, rulerPositionZ));
		model = glm::scale(model, glm::vec3(rulerSizeX, rulerSizeY, rulerSizeZ));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);*/

		glBindVertexArray(VAO[0]);
		glBindTexture(GL_TEXTURE_2D, texture_baby_yoda);

		/* Baby Yoda */

		float thirdPersonCameraAngle = 180.0f;
		glm::vec3 thirdPersonCameraCenter = glm::vec3(0.0f * scale, 0.0f * scale, 6.3333f * scale);
		if (camera.Mode == CAMERA_THIRD_PERSON) {
			camera.Center.y += baby_yoda_delta_offset_y * scale;
			camera.Position.y += baby_yoda_delta_offset_y * scale;
			thirdPersonCameraAngle = -camera.Yaw + 90.0;
			thirdPersonCameraCenter = glm::vec3(camera.Center.x, camera.Center.y, camera.Center.z);
		}

		float BABY_YODA_SCALE = 50.0f;

		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBindTexture(GL_TEXTURE_2D, texture_baby_yoda);

		// UPPER BODY
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(upperBodyTextureCoordsBuffer), upperBodyTextureCoordsBuffer);
		model = glm::translate(glm::mat4(1.0f), thirdPersonCameraCenter + glm::vec3(0.0f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale) + glm::vec3(0.0f * scale, 0.2f * scale, 0.0f * scale));
		modelBabyYodaBody = model = glm::rotate(model, glm::radians(thirdPersonCameraAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(14.0f / BABY_YODA_SCALE * scale, 4.0f / BABY_YODA_SCALE * scale, 14.0f / BABY_YODA_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// HEAD
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(headTextureCoordsBuffer), headTextureCoordsBuffer);
		model = glm::translate(modelBabyYodaBody, glm::vec3(0.0f / BABY_YODA_SCALE * scale, 10.0f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale));
		model = glm::scale(model, glm::vec3(12.0f / BABY_YODA_SCALE * scale, 12.0f / BABY_YODA_SCALE * scale, 12.0f / BABY_YODA_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// NECK
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(neckTextureCoordsBuffer), neckTextureCoordsBuffer);
		model = glm::translate(modelBabyYodaBody, glm::vec3(0.0f / BABY_YODA_SCALE * scale, 4.5f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale));
		model = glm::scale(model, glm::vec3(16.0f / BABY_YODA_SCALE * scale, 5.0f / BABY_YODA_SCALE * scale, 16.0f / BABY_YODA_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// LOWER BODY
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(lowerBodyTextureCoordsBuffer), lowerBodyTextureCoordsBuffer);
		model = glm::translate(modelBabyYodaBody, glm::vec3(0.0f / BABY_YODA_SCALE * scale, -5.5f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale));
		model = glm::scale(model, glm::vec3(15.0f / BABY_YODA_SCALE * scale, 7.0f / BABY_YODA_SCALE * scale, 15.0f / BABY_YODA_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// RIGHT ARM
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(armTextureCoordsBuffer), armTextureCoordsBuffer);
		model = glm::translate(modelBabyYodaBody, glm::vec3(5.8f / BABY_YODA_SCALE * scale, 0.5f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale));
		model = glm::rotate(model, glm::radians(baby_yoda_right_arm_rotate_z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(baby_yoda_right_arm_rotate_y), glm::vec3(0.0f, 1.0f, 0.0f));
		modelBabyYodaArms = model = glm::translate(model, glm::vec3(3.5f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale));
		model = glm::scale(model, glm::vec3(7.0f / BABY_YODA_SCALE * scale, 7.0f / BABY_YODA_SCALE * scale, 7.0f / BABY_YODA_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// RIGHT HAND
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(handTextureCoordsBuffer), handTextureCoordsBuffer);
		model = glm::translate(modelBabyYodaArms, glm::vec3(5.5f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale));
		model = glm::scale(model, glm::vec3(4.0f / BABY_YODA_SCALE * scale, 4.0f / BABY_YODA_SCALE * scale, 4.0f / BABY_YODA_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// LEFT ARM
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(armTextureCoordsBuffer), armTextureCoordsBuffer);
		model = glm::translate(modelBabyYodaBody, glm::vec3(-5.8f / BABY_YODA_SCALE * scale, 0.5f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale));
		model = glm::rotate(model, glm::radians(baby_yoda_left_arm_rotate_z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(baby_yoda_left_arm_rotate_y), glm::vec3(0.0f, 1.0f, 0.0f));
		modelBabyYodaArms = model = glm::translate(model, glm::vec3(-3.5f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale));
		model = glm::scale(model, glm::vec3(7.0f / BABY_YODA_SCALE * scale, 7.0f / BABY_YODA_SCALE * scale, 7.0f / BABY_YODA_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// LEFT HAND
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(handTextureCoordsBuffer), handTextureCoordsBuffer);
		model = glm::translate(modelBabyYodaArms, glm::vec3(-5.5f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale, 0.0f / BABY_YODA_SCALE * scale));
		model = glm::scale(model, glm::vec3(4.0f / BABY_YODA_SCALE * scale, 4.0f / BABY_YODA_SCALE * scale, 4.0f / BABY_YODA_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		/* MIKE WAZOWSKI */

		float MIKE_SCALE = 12.5f;

		glBindTexture(GL_TEXTURE_2D, texture_mike_wazowski);

		// Cuerpo y Cara
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(headMikeTextureCoordsBuffer), headMikeTextureCoordsBuffer);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(24.5f * scale, 0.69f * scale, -15.0f * scale));
		model = modelMikeWazowski = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f / MIKE_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brazo Derecho
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bodyMikeTextureCoordsBuffer), bodyMikeTextureCoordsBuffer);
		model = glm::translate(modelMikeWazowski, glm::vec3(3.0f / MIKE_SCALE * scale, -2.5f / MIKE_SCALE * scale, 0.0f / MIKE_SCALE * scale));
		model = glm::scale(model, glm::vec3(1.0f / MIKE_SCALE * scale, 4.0f / MIKE_SCALE * scale, 1.0f / MIKE_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brazo Izquierdo
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bodyMikeTextureCoordsBuffer), bodyMikeTextureCoordsBuffer);
		model = glm::translate(modelMikeWazowski, glm::vec3(-3.0f / MIKE_SCALE * scale, -2.5f / MIKE_SCALE * scale, 0.0f / MIKE_SCALE * scale));
		model = glm::scale(model, glm::vec3(1.0f / MIKE_SCALE * scale, 4.0f / MIKE_SCALE * scale, 1.0f / MIKE_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pierna Derecha
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bodyMikeTextureCoordsBuffer), bodyMikeTextureCoordsBuffer);
		model = glm::translate(modelMikeWazowski, glm::vec3(1.5f / MIKE_SCALE * scale, -5.0f / MIKE_SCALE * scale, 0.0f / MIKE_SCALE * scale));
		model = glm::scale(model, glm::vec3(1.5f / MIKE_SCALE * scale, 5.0f / MIKE_SCALE * scale, 1.0f / MIKE_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pierna Izquierda
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bodyMikeTextureCoordsBuffer), bodyMikeTextureCoordsBuffer);
		model = glm::translate(modelMikeWazowski, glm::vec3(-1.5f / MIKE_SCALE * scale, -5.0f / MIKE_SCALE * scale, 0.0f / MIKE_SCALE * scale));
		model = glm::scale(model, glm::vec3(1.5f / MIKE_SCALE * scale, 5.0f / MIKE_SCALE * scale, 1.0f / MIKE_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pie Derecho
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bodyMikeTextureCoordsBuffer), bodyMikeTextureCoordsBuffer);
		model = glm::translate(modelMikeWazowski, glm::vec3(1.5f / MIKE_SCALE * scale, -7.25f / MIKE_SCALE * scale, 1.0f / MIKE_SCALE * scale));
		model = glm::scale(model, glm::vec3(1.5f / MIKE_SCALE * scale, 0.5f / MIKE_SCALE * scale, 1.0f / MIKE_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36); 

		// Pie Izquierdo
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bodyMikeTextureCoordsBuffer), bodyMikeTextureCoordsBuffer);
		model = glm::translate(modelMikeWazowski, glm::vec3(-1.5f / MIKE_SCALE * scale, -7.25f / MIKE_SCALE * scale, 1.0f / MIKE_SCALE * scale));
		model = glm::scale(model, glm::vec3(1.5f / MIKE_SCALE * scale, 0.5f / MIKE_SCALE * scale, 1.0f / MIKE_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerno Derecho Parte 1
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bodyMikeTextureCoordsBuffer), bodyMikeTextureCoordsBuffer);
		model = glm::translate(modelMikeWazowski, glm::vec3(1.5f / MIKE_SCALE * scale, 3.25f / MIKE_SCALE * scale, -1.0f / MIKE_SCALE * scale));
		model = glm::scale(model, glm::vec3(0.5f / MIKE_SCALE * scale, 1.5f / MIKE_SCALE * scale, 0.5f / MIKE_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 100.0f, 100.0f, 100.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerno Derecho Parte 2
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bodyMikeTextureCoordsBuffer), bodyMikeTextureCoordsBuffer);
		model = glm::translate(modelMikeWazowski, glm::vec3(1.5f / MIKE_SCALE * scale, 3.0f / MIKE_SCALE * scale, -0.5f / MIKE_SCALE * scale));
		model = glm::scale(model, glm::vec3(0.5f / MIKE_SCALE * scale, 1.0f / MIKE_SCALE * scale, 0.5f / MIKE_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 100.0f, 100.0f, 100.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerno Derecho Parte 3
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bodyMikeTextureCoordsBuffer), bodyMikeTextureCoordsBuffer);
		model = glm::translate(modelMikeWazowski, glm::vec3(1.5f / MIKE_SCALE * scale, 2.75f / MIKE_SCALE * scale, 0.0f / MIKE_SCALE * scale));
		model = glm::scale(model, glm::vec3(0.5f / MIKE_SCALE * scale, 0.5f / MIKE_SCALE * scale, 0.5f / MIKE_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 100.0f, 100.0f, 100.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerno Izquierdo Parte 1
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bodyMikeTextureCoordsBuffer), bodyMikeTextureCoordsBuffer);
		model = glm::translate(modelMikeWazowski, glm::vec3(-1.5f / MIKE_SCALE * scale, 3.25f / MIKE_SCALE * scale, -1.0f / MIKE_SCALE * scale));
		model = glm::scale(model, glm::vec3(0.5f / MIKE_SCALE * scale, 1.5f / MIKE_SCALE * scale, 0.5f / MIKE_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 100.0f, 100.0f, 100.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerno Izquierdo Parte 2
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bodyMikeTextureCoordsBuffer), bodyMikeTextureCoordsBuffer);
		model = glm::translate(modelMikeWazowski, glm::vec3(-1.5f / MIKE_SCALE * scale, 3.0f / MIKE_SCALE * scale, -0.5f / MIKE_SCALE * scale));
		model = glm::scale(model, glm::vec3(0.5f / MIKE_SCALE * scale, 1.0f / MIKE_SCALE * scale, 0.5f / MIKE_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 100.0f, 100.0f, 100.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerno Izquierdo Parte 3
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bodyMikeTextureCoordsBuffer), bodyMikeTextureCoordsBuffer);
		model = glm::translate(modelMikeWazowski, glm::vec3(-1.5f / MIKE_SCALE * scale, 2.75f / MIKE_SCALE * scale, 0.0f / MIKE_SCALE * scale));
		model = glm::scale(model, glm::vec3(0.5f / MIKE_SCALE * scale, 0.5f / MIKE_SCALE * scale, 0.5f / MIKE_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 100.0f, 100.0f, 100.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		/* Aang */
		float Aang_SCALE = 25.0f;
		glBindTexture(GL_TEXTURE_2D, texture_aang);

		//Head
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(headAangTextureCoordsBuffer), headAangTextureCoordsBuffer);
		model = glm::translate(glm::mat4(1.0f), aang_position);
		model = modelAang = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3( 16.0f / Aang_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Body
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bodyAangTextureCoordsBuffer), bodyAangTextureCoordsBuffer);
		model = glm::translate(modelAang, glm::vec3(0.0f / Aang_SCALE * scale, -14.5f / Aang_SCALE * scale, 0.0f / Aang_SCALE * scale));
		model = glm::rotate(model, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f / Aang_SCALE * scale, 13.0f / Aang_SCALE * scale, 4.0f / Aang_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Right Ear
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(earAangTextureCoordsBuffer), earAangTextureCoordsBuffer);
		model = glm::translate(modelAang, glm::vec3(8.5f / Aang_SCALE * scale, 0.0f / Aang_SCALE * scale, 0.0f / Aang_SCALE * scale));
		model = glm::scale(model, glm::vec3(1.0f / Aang_SCALE * scale, 4.0f / Aang_SCALE * scale, 2.0f / Aang_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Left Ear
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(earAangTextureCoordsBuffer), earAangTextureCoordsBuffer);
		model = glm::translate(modelAang, glm::vec3(-8.5f / Aang_SCALE * scale, 0.0f / Aang_SCALE * scale, 0.0f / Aang_SCALE * scale));
		model = glm::scale(model, glm::vec3(1.0f / Aang_SCALE * scale, 4.0f / Aang_SCALE * scale, 2.0f / Aang_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Right Arm
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(armAangTextureCoordsBuffer), armAangTextureCoordsBuffer);
		model = glm::translate(modelAang, glm::vec3(6.0f / Aang_SCALE * scale, -12.0f / Aang_SCALE * scale, 0.0f / Aang_SCALE * scale));
		model = glm::rotate(model, glm::radians(18.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(2.5f / Aang_SCALE * scale, 7.5f / Aang_SCALE * scale, 2.5f / Aang_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Left Arm
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(armAangTextureCoordsBuffer), armAangTextureCoordsBuffer);
		model = glm::translate(modelAang, glm::vec3(-6.0f / Aang_SCALE * scale, -12.0f / Aang_SCALE * scale, 0.0f / Aang_SCALE * scale));
		model = glm::rotate(model, glm::radians(18.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(2.5f / Aang_SCALE * scale, 7.5f / Aang_SCALE * scale, 2.5f / Aang_SCALE * scale));
		model = glm::rotate(model, glm::radians(180.0f) ,glm::vec3(0.0f, 1.0f, 0.0f));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Right Leg
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(legAangTextureCoordsBuffer), legAangTextureCoordsBuffer);
		model = glm::translate(modelAang, glm::vec3(2.0f / Aang_SCALE * scale, -(20.0f + 5.0f * 0.7f) / Aang_SCALE * scale, -2.0f / Aang_SCALE * scale));
		modelAangRightLeg = model = glm::rotate(model, glm::radians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f / Aang_SCALE * scale, (10.0f * 0.7f)/ Aang_SCALE * scale, 3.0f / Aang_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Left Leg
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(legAangTextureCoordsBuffer), legAangTextureCoordsBuffer);
		model = glm::translate(modelAang, glm::vec3(-2.0f / Aang_SCALE * scale, -(21.0f + 5.0f * 0.7f) / Aang_SCALE * scale, -3.0f / Aang_SCALE * scale));
		modelAangLeftLeg = model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f / Aang_SCALE * scale, (10.0f * 0.7f) / Aang_SCALE * scale, 3.0f / Aang_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Right Shoe
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(shoeAangTextureCoordsBuffer), shoeAangTextureCoordsBuffer);
		model = glm::translate(modelAangRightLeg, glm::vec3(0.0f / Aang_SCALE * scale, -( 4.0f * 0.7f) / Aang_SCALE * scale, 2.25f / Aang_SCALE * scale));
		model = glm::scale(model, glm::vec3(3.0f / Aang_SCALE * scale, (2.0f * 0.7f) / Aang_SCALE * scale, 1.5f / Aang_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Left Shoe
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(shoeAangTextureCoordsBuffer), shoeAangTextureCoordsBuffer);
		model = glm::translate(modelAangLeftLeg, glm::vec3(0.0f / Aang_SCALE * scale, -( 4.0f * 0.7f) / Aang_SCALE * scale, 2.25f / Aang_SCALE * scale));
		model = glm::scale(model, glm::vec3(3.0f / Aang_SCALE * scale, (2.0f * 0.7f) / Aang_SCALE * scale, 1.5f / Aang_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Right Shoe Part 1
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(shoeUpAangTextureCoordsBuffer), shoeUpAangTextureCoordsBuffer);
		model = glm::translate(modelAangRightLeg, glm::vec3(0.0f / Aang_SCALE * scale, -( 3.0f * 0.7f) / Aang_SCALE * scale, 1.875f / Aang_SCALE * scale));
		model = glm::scale(model, glm::vec3(3.0f / Aang_SCALE * scale, (1.0f * 0.7f) / Aang_SCALE * scale, 0.75f / Aang_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Left Shoe Part 1
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(shoeUpAangTextureCoordsBuffer), shoeUpAangTextureCoordsBuffer);
		model = glm::translate(modelAangLeftLeg, glm::vec3(0.0f / Aang_SCALE * scale, -( 3.0f * 0.7f) / Aang_SCALE * scale, 1.875f / Aang_SCALE * scale));
		model = glm::scale(model, glm::vec3(3.0f / Aang_SCALE * scale, (1.0f * 0.7f) / Aang_SCALE * scale, 0.75f / Aang_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Fuego
		glBindTexture(GL_TEXTURE_2D, texture_fire);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(FireAangTextureCoordsBuffer), FireAangTextureCoordsBuffer);
		model = glm::translate(modelAang, glm::vec3(0.0f / Aang_SCALE * scale, -13.0f / Aang_SCALE * scale, 0.0f / Aang_SCALE * scale));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(-fire_rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(50.0f / Aang_SCALE * scale, 10.0f / Aang_SCALE * scale, 50.0f / Aang_SCALE * scale));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// TOROIDES
		glBindVertexArray(torus.getVAO());

		// Flotador
		glBindTexture(GL_TEXTURE_2D, texture_pool_float);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(pool_float_offset_x * scale, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, pool_float_offset_z * scale));
		model = glm::translate(model, glm::vec3(-17.20f * scale, 1.85f, -16.45f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75f));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		torus.draw();

		// Dona
		glBindTexture(GL_TEXTURE_2D, texture_donut);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(13.0f * scale, 1.08f * scale, -24.25f * scale));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.13f));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		torus.draw();

		// Dona Columpio
		glBindTexture(GL_TEXTURE_2D, texture_swing_lifesaver);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-84.07f * scale, 1.885f * scale, 19.135f * scale));
		model = glm::scale(model, glm::vec3(0.5f));
		shaderCube.setMat4("model", model);
		shaderCube.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		torus.draw();

		shaderSkybox.use();
		skybox.Draw(shaderSkybox, view, projection, camera);

		/* AUDIO */

		alListener3f(AL_POSITION, camera.Center.x, camera.Center.y, camera.Center.z);

		// Audio Naturaleza
		alSource3f(sources[1], AL_POSITION, camera.Center.x, camera.Center.y, camera.Center.z);

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

	alDeleteSources(3, sources);
	alDeleteBuffers(2, buffers);
	alDeleteBuffers(4, song_buffers);
	ALCcontext* context = alcGetCurrentContext();
	ALCdevice* device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);

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
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		modelPositionX += modelPositionStep;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		modelPositionY += modelPositionStep;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		modelPositionZ += modelPositionStep;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		modelPositionStep *= -1;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		std::cout << "Position is: " << modelPositionX << ", " << modelPositionY << ", " << modelPositionZ << std::endl;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		camera.setCameraMode(CAMERA_AERIAL);
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		camera.setCameraMode(CAMERA_THIRD_PERSON);
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		camera.setCameraMode(CAMERA_FREE);
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		if (baby_yoda_levitating) {
			baby_yoda_should_save_initial_values = true;
			baby_yoda_levitation_stage = BABY_YODA_TO_NORMAL_ARMS;
		}
		if (!baby_yoda_levitating) {
			baby_yoda_levitating = true;
			baby_yoda_should_save_initial_values = true;
			baby_yoda_levitation_stage = BABY_YODA_PREPARING_ARMS;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		if (camera.isWithinRadiusOfPosition(speakers_position, 6.0 * scale) && camera.isLookingAtPosition(speakers_position, 45.0f)) {
			load_next_song();
		}
	}
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