#pragma once

#ifndef TEXTURES_BABY_YODA
#define TEXTURES_BABY_YODA

#include <glad/glad.h>

float TEX_WIDTH = 68.0f;
float TEX_HEIGHT = 37.0f;

GLfloat headTextureCoordsBuffer[72];
GLfloat neckTextureCoordsBuffer[72];
GLfloat upperBodyTextureCoordsBuffer[72];
GLfloat lowerBodyTextureCoordsBuffer[72];
GLfloat armTextureCoordsBuffer[72];
GLfloat handTextureCoordsBuffer[72];

void loadTextureDataBabyYoda() {

	GLfloat headTextureCoords[72] = {
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),

		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 0.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 0.0f) / TEX_HEIGHT),
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 0.0f) / TEX_HEIGHT),

		(24.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
		(24.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(24.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),

		(32.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(32.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
		(24.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
		(32.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(24.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(24.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),

		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(0.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(0.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
		(0.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),

		(24.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 0.0f) / TEX_HEIGHT),
		(24.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(24.0f / TEX_WIDTH), ((TEX_HEIGHT - 0.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 0.0f) / TEX_HEIGHT),
	};

	GLfloat neckTextureCoords[72] = {
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
		(18.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
		(18.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(18.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),

		(28.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
		(18.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
		(18.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(28.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
		(28.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(18.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),

		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(0.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(0.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
		(0.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),

		(36.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(36.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
		(28.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
		(36.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(28.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(28.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),

		(18.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(18.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
		(18.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(8.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),

		(28.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(18.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(18.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
		(28.0f / TEX_WIDTH), ((TEX_HEIGHT - 24.0f) / TEX_HEIGHT),
		(28.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
		(18.0f / TEX_WIDTH), ((TEX_HEIGHT - 16.0f) / TEX_HEIGHT),
	};

	GLfloat upperBodyTextureCoords[72] = {
		(7.0f / TEX_WIDTH), ((TEX_HEIGHT - 37.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 37.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(7.0f / TEX_WIDTH), ((TEX_HEIGHT - 37.0f) / TEX_HEIGHT),
		(7.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),

		(25.0f / TEX_WIDTH), ((TEX_HEIGHT - 37.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 37.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(25.0f / TEX_WIDTH), ((TEX_HEIGHT - 37.0f) / TEX_HEIGHT),
		(25.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),

		(7.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(0.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(0.0f / TEX_WIDTH), ((TEX_HEIGHT - 37.0f) / TEX_HEIGHT),
		(0.0f / TEX_WIDTH), ((TEX_HEIGHT - 37.0f) / TEX_HEIGHT),
		(7.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(7.0f / TEX_WIDTH), ((TEX_HEIGHT - 37.0f) / TEX_HEIGHT),

		(32.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(32.0f / TEX_WIDTH), ((TEX_HEIGHT - 37.0f) / TEX_HEIGHT),
		(25.0f / TEX_WIDTH), ((TEX_HEIGHT - 37.0f) / TEX_HEIGHT),
		(32.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(25.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(25.0f / TEX_WIDTH), ((TEX_HEIGHT - 37.0f) / TEX_HEIGHT),

		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(7.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(7.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
		(7.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),

		(25.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
		(25.0f / TEX_WIDTH), ((TEX_HEIGHT - 34.0f) / TEX_HEIGHT),
		(25.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
		(16.0f / TEX_WIDTH), ((TEX_HEIGHT - 27.0f) / TEX_HEIGHT),
	};

	GLfloat lowerBodyTextureCoords[72] = {
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 13.0f) / TEX_HEIGHT),
		(50.0f / TEX_WIDTH), ((TEX_HEIGHT - 13.0f) / TEX_HEIGHT),
		(50.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 13.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(50.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),

		(60.0f / TEX_WIDTH), ((TEX_HEIGHT - 13.0f) / TEX_HEIGHT),
		(50.0f / TEX_WIDTH), ((TEX_HEIGHT - 13.0f) / TEX_HEIGHT),
		(50.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(60.0f / TEX_WIDTH), ((TEX_HEIGHT - 13.0f) / TEX_HEIGHT),
		(60.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(50.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),

		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(32.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(32.0f / TEX_WIDTH), ((TEX_HEIGHT - 13.0f) / TEX_HEIGHT),
		(32.0f / TEX_WIDTH), ((TEX_HEIGHT - 13.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 13.0f) / TEX_HEIGHT),

		(68.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(68.0f / TEX_WIDTH), ((TEX_HEIGHT - 13.0f) / TEX_HEIGHT),
		(60.0f / TEX_WIDTH), ((TEX_HEIGHT - 13.0f) / TEX_HEIGHT),
		(68.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(60.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(60.0f / TEX_WIDTH), ((TEX_HEIGHT - 13.0f) / TEX_HEIGHT),

		(50.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 0.0f) / TEX_HEIGHT),
		(50.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(50.0f / TEX_WIDTH), ((TEX_HEIGHT - 0.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 0.0f) / TEX_HEIGHT),

		(50.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(50.0f / TEX_WIDTH), ((TEX_HEIGHT - 0.0f) / TEX_HEIGHT),
		(60.0f / TEX_WIDTH), ((TEX_HEIGHT - 0.0f) / TEX_HEIGHT),
		(50.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
		(60.0f / TEX_WIDTH), ((TEX_HEIGHT - 0.0f) / TEX_HEIGHT),
		(60.0f / TEX_WIDTH), ((TEX_HEIGHT - 8.0f) / TEX_HEIGHT),
	};

	GLfloat armTextureCoords[72] = {
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),

		(48.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(48.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(48.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),

		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(36.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(36.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(36.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),

		(52.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(52.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(48.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(52.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(48.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(48.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),

		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 21.0f) / TEX_HEIGHT),
		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 21.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 21.0f) / TEX_HEIGHT),

		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 21.0f) / TEX_HEIGHT),
		(48.0f / TEX_WIDTH), ((TEX_HEIGHT - 21.0f) / TEX_HEIGHT),
		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
		(48.0f / TEX_WIDTH), ((TEX_HEIGHT - 21.0f) / TEX_HEIGHT),
		(48.0f / TEX_WIDTH), ((TEX_HEIGHT - 25.0f) / TEX_HEIGHT),
	};

	GLfloat handTextureCoords[72] = {
		(36.0f / TEX_WIDTH), ((TEX_HEIGHT - 32.0f) / TEX_HEIGHT),
		(38.0f / TEX_WIDTH), ((TEX_HEIGHT - 32.0f) / TEX_HEIGHT),
		(38.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(36.0f / TEX_WIDTH), ((TEX_HEIGHT - 32.0f) / TEX_HEIGHT),
		(36.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(38.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),

		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 32.0f) / TEX_HEIGHT),
		(38.0f / TEX_WIDTH), ((TEX_HEIGHT - 32.0f) / TEX_HEIGHT),
		(38.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 32.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(38.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),

		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(42.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(42.0f / TEX_WIDTH), ((TEX_HEIGHT - 32.0f) / TEX_HEIGHT),
		(42.0f / TEX_WIDTH), ((TEX_HEIGHT - 32.0f) / TEX_HEIGHT),
		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(44.0f / TEX_WIDTH), ((TEX_HEIGHT - 32.0f) / TEX_HEIGHT),

		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 32.0f) / TEX_HEIGHT),
		(42.0f / TEX_WIDTH), ((TEX_HEIGHT - 32.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(42.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(42.0f / TEX_WIDTH), ((TEX_HEIGHT - 32.0f) / TEX_HEIGHT),

		(42.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(42.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(42.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),

		(38.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(38.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(38.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 28.0f) / TEX_HEIGHT),
		(40.0f / TEX_WIDTH), ((TEX_HEIGHT - 30.0f) / TEX_HEIGHT),
	};

	for (int i = 0; i < 72; i++) {
		headTextureCoordsBuffer[i] = headTextureCoords[i];
		neckTextureCoordsBuffer[i] = neckTextureCoords[i];
		upperBodyTextureCoordsBuffer[i] = upperBodyTextureCoords[i];
		lowerBodyTextureCoordsBuffer[i] = lowerBodyTextureCoords[i];
		armTextureCoordsBuffer[i] = armTextureCoords[i];
		handTextureCoordsBuffer[i] = handTextureCoords[i];
	}
}

#endif // !


