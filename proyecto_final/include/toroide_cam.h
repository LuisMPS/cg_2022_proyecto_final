#pragma once

#ifndef TOROIDECA_H
#define TOROIDECA_H

#include <glad/glad.h>

#include <vector>
#include <cmath>

class Toroide_cam {

	public:
		float Radio_ext;
		float Radio_int;
		int Resolucion_ext;
		int Resolucion_int;
		std::vector<float> data;
		GLuint VAO;
		GLuint VBO;
		Toroide_cam(float Radio_ext, float Radio_int, int Resolucion_ext, int Resolucion_int) {
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			setParameters(Radio_ext, Radio_int, Resolucion_ext, Resolucion_int);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data[0], GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		~Toroide_cam() {

		}
		GLuint getVAO() {
			return VAO;
		}
		GLuint getVBO() {
			return VBO;
		}
		void draw() {
			glDrawArrays(GL_TRIANGLE_STRIP, 0, data.size());
		}
		void setRadio_ext(float Radio_ext) {
			setParameters(Radio_ext, Radio_int, Resolucion_ext, Resolucion_int);
		}
		void setRadio_int(float Radio_int) {
			setParameters(Radio_ext, Radio_int, Resolucion_ext, Resolucion_int);
		}
		void setResolucion_ext(int Resolucion_ext) {
			setParameters(Radio_ext, Radio_int, Resolucion_ext, Resolucion_int);
		}
		void setResolucion_int(int Resolucion_int) {
			setParameters(Radio_ext, Radio_int, Resolucion_ext, Resolucion_int);
		}
		void setParameters(float Radio_ext, float Radio_int, int Resolucion_ext, int Resolucion_int) {
			data.clear();
			float Tau = 2 * M_PI;
			for (int i = 0; i < Resolucion_ext; i++) {
				for (int j = 0; j <= Resolucion_int; j++) {
					for (int k = 0; k <= 1; k++) {
						double s = (i + k) % Resolucion_int + 0.5;
						double t = j % (Resolucion_ext + 1);

						double x = (Radio_ext + Radio_int * cos(s * Tau / Resolucion_int)) * cos(t * Tau / Resolucion_ext);
						double y = (Radio_ext + Radio_int * cos(s * Tau / Resolucion_int)) * sin(t * Tau / Resolucion_ext);
						double z = Radio_int * sin(s * Tau / Resolucion_int);

						data.push_back(x);
						data.push_back(y);
						data.push_back(z);

						double u = (i + k) / (float) Resolucion_ext;
						double v = t / (float) Resolucion_int;

						data.push_back(u);
						data.push_back(v);
					}
				}
			}
		}
};

#endif