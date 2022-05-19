#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

enum CameraMode {
	CAMERA_THIRD_PERSON,
	CAMERA_FREE,
	CAMERA_AERIAL,
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  0.5f;
const float SENSITIVITY =  0.5f;
const float ZOOM        =  45.0f;
const float RADIUS		=  20.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
	public:
		// Camera Attributes
		glm::vec3 Position;
		glm::vec3 Center;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;
		// Euler Angles
		float Yaw;
		float Pitch;
		// Camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;
		CameraMode Mode;

		// Constructor with vectors
		Camera(glm::vec3 center = glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM), Mode(CAMERA_FREE) {
			Center = center;
			Position = Center + glm::vec3(0.0f, 10.0f, 0.0f);
			WorldUp = up;
			Yaw = yaw;
			Pitch = pitch;
			updateCameraVectors();
		}

		// Constructor with scalar values
		Camera(float centerX, float centerY, float centerZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM), Mode(CAMERA_FREE) {
			Center = glm::vec3(centerX, centerY, centerZ);
			Position = Center + glm::vec3(0.0f, 10.0f, 0.0f);
			WorldUp = glm::vec3(upX, upY, upZ);
			Yaw = yaw;
			Pitch = pitch;
			updateCameraVectors();
		}

		// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
		glm::mat4 GetViewMatrix() {
			return glm::lookAt(Position, Position + Front, Up);
		}

		// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
		void ProcessKeyboard(CameraMovement direction, float deltaTime) {
			float velocity = MovementSpeed * deltaTime;
			if (direction == FORWARD) {
				if (Mode == CAMERA_AERIAL) {
					glm::vec3 movement = Up * velocity;
					Center += movement;
					Position += movement;
				}
				else if (Mode == CAMERA_THIRD_PERSON) {
					glm::vec3 movement = glm::normalize(glm::cross(WorldUp, Right)) * velocity;
					Position += movement;
					Center += movement;
				}
				else if (Mode == CAMERA_FREE) {
					glm::vec3 movement = Front * velocity;
					Position += movement;
					Center += movement;
				}

			}
			if (direction == BACKWARD) {
				if (Mode == CAMERA_AERIAL) {
					glm::vec3 movement = Up * velocity;
					Center -= movement;
					Position -= movement;
				}
				else if (Mode == CAMERA_THIRD_PERSON) {
					glm::vec3 movement = glm::normalize(glm::cross(WorldUp, Right)) * velocity;
					Position -= movement;
					Center -= movement;
				}
				else if (Mode == CAMERA_FREE) {
					glm::vec3 movement = Front * velocity;
					Position -= movement;
					Center -= movement;
				}
			}
			if (direction == RIGHT) {
				glm::vec3 movement = Right * velocity;
				Position += movement;
				Center += movement;
			}
			if (direction == LEFT) {
				glm::vec3 movement = Right * velocity;
				Position -= movement;
				Center -= movement;
			}
		}

		// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
			// Disable yaw/pitch adjustments in aerial camera mode
			if (Mode == CAMERA_AERIAL) {
				return;
			}
			else if (Mode == CAMERA_THIRD_PERSON) {
				xoffset *= MouseSensitivity;
				yoffset *= MouseSensitivity;
				Yaw += xoffset;
				Pitch -= yoffset;
				if (constrainPitch) {
					if (Pitch > 0.0f) {
						Pitch = 0.0f;
					}
					if (Pitch < -45.0f) {
						Pitch = -45.0f;
					}
				}
				Position = Center - glm::vec3(
					RADIUS * cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)),
					RADIUS * sin(glm::radians(Pitch)),
					RADIUS * sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))
				);
			}
			else if (Mode == CAMERA_FREE) {
				xoffset *= MouseSensitivity;
				yoffset *= MouseSensitivity;
				Yaw += xoffset;
				Pitch += yoffset;
				// Make sure that when pitch is out of bounds, screen doesn't get flipped
				if (constrainPitch) {
					if (Pitch > 89.0f) {
						Pitch = 89.0f;
					}
					if (Pitch < -89.0f) {
						Pitch = -89.0f;
					}
				}
			}
			// Update Front, Right and Up Vectors using the updated Euler angles
			updateCameraVectors();
		}

		// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
		void ProcessMouseScroll(float yoffset) {
			if (Zoom >= 1.0f && Zoom <= 45.0f) {
				Zoom -= yoffset;
			}
			if (Zoom <= 1.0f) {
				Zoom = 1.0f;
			}
			if (Zoom >= 45.0f) {
				Zoom = 45.0f;
			}
		}

		void move(glm::vec3 direction) {
			if (Mode == CAMERA_FREE || Mode == CAMERA_AERIAL) {
				glm::vec3 initialCenter = Center;
				Position = initialCenter + direction;
				Center = initialCenter + direction;
			}
			if (Mode == CAMERA_THIRD_PERSON) {
				glm::vec3 initialCenter = Center;
				Position = initialCenter + direction - glm::vec3(
					RADIUS * cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)),
					RADIUS * sin(glm::radians(Pitch)),
					RADIUS * sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))
				);
				Center = initialCenter + direction;
			}
		}

		void moveTo(glm::vec3 position) {
			if (Mode == CAMERA_FREE || Mode == CAMERA_AERIAL) {
				Position = position;
				Center = position;
			}
			if (Mode == CAMERA_THIRD_PERSON) {
				Position = position - glm::vec3(
					RADIUS * cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)),
					RADIUS * sin(glm::radians(Pitch)),
					RADIUS * sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))
				);
				Center = position;
			}
		}

		void setCameraMode(CameraMode Mode) {
			if (this->Mode == Mode) return;
			this->Mode = Mode;
			switch (Mode) {
				case CAMERA_FREE:
					Yaw = -90.0f;
					Pitch = 0.0f;
					break;
				case CAMERA_THIRD_PERSON:
					Yaw = -90.0f;
					Pitch = -30.0f;
					break;
				case CAMERA_AERIAL:
					Yaw = -90.0f;
					Pitch = -90.0f;
					break;
			}
			updateCameraVectors();
		}

		bool isWithinRadiusOfPosition(glm::vec3 position, float radius) {
			float distance = glm::distance(position, Center);
			//std::cout << distance << std::endl;
			return distance < radius;
		}

		bool isLookingAtPosition(glm::vec3 position, float toleranceAngle) {
			glm::vec3 normalized_front = glm::normalize(Front);
			glm::vec3 normalized_direction = glm::normalize(position - Center);
			float angle = glm::degrees(acos(glm::dot(normalized_front, normalized_direction)));
			//std::cout << angle << std::endl;
			if (angle < toleranceAngle) return true;
			else return false;
		}

	private:

		// Calculates the front vector from the Camera's (updated) Euler Angles
		void updateCameraVectors() {
			// Calculate the new Front vector
			glm::vec3 front;
			front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			front.y = sin(glm::radians(Pitch));
			front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			Front = glm::normalize(front);
			// Also re-calculate the Right and Up vector
			Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			Up = glm::normalize(glm::cross(Right, Front));
		}
};
#endif