#pragma once

#ifndef TORUS_H
#define TORUS_H

#include <glad/glad.h>

#include <vector>
#include <cmath>

class Torus {

	public:
		float outerRadius;
		float innerRadius;
		int outerResolution;
		int innerResolution;
		std::vector<float> data;
		GLuint VAO;
		GLuint VBO;
		Torus(float outerRadius, float innerRadius, int outerResolution, int innerResolution) {
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			setParameters(outerRadius, innerRadius, outerResolution, innerResolution);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data[0], GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		~Torus() {

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
		void setOuterRadius(float outerRadius) {
			setParameters(outerRadius, innerRadius, outerResolution, innerResolution);
		}
		void setInnerRadius(float innerRadius) {
			setParameters(outerRadius, innerRadius, outerResolution, innerResolution);
		}
		void setOuterResolution(int outerResolution) {
			setParameters(outerRadius, innerRadius, outerResolution, innerResolution);
		}
		void setInnerResolution(int innerResolution) {
			setParameters(outerRadius, innerRadius, outerResolution, innerResolution);
		}
		void setParameters(float outerRadius, float innerRadius, int outerResolution, int innerResolution) {
			data.clear();
			float du = 2 * M_PI / outerResolution;
			float dv = 2 * M_PI / innerResolution;
			for (auto i = 0; i < outerResolution; i++) {
				float u = i * du;
				for (auto j = 0; j <= innerResolution; j++) {
					float v = (j % innerResolution) * dv;
					for (auto k = 0; k < 2; k++) {
						float uu = u + k * du;
						// compute vertex
						float x = (outerRadius + innerRadius * cos(v)) * cos(uu);
						float y = (outerRadius + innerRadius * cos(v)) * sin(uu);
						float z = innerRadius * sin(v);
						// add vertex 
						data.push_back(x);
						data.push_back(y);
						data.push_back(z);
						// compute texture coords
						float tx = uu / (2 * M_PI);
						float ty = v / (2 * M_PI);
						// add tex coords
						data.push_back(tx);
						data.push_back(ty);
					}
					// incr angle
					v += dv;
				}
			}
		}
};

#endif