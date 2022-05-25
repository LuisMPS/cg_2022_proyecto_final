#pragma once

#ifndef DONA_H
#define DONA_H

#include <glad/glad.h>

#include <vector>
#include <cmath>


class Toroide_dona {

public:
	float radioExterno;
	float radioInterno;
	int resolucionExterior;
	int resolucionInterior;
	std::vector<float> data;
	GLuint VAO;
	GLuint VBO;


	Toroide_dona(float radioExterno, float radioInterno, int resolucionExterior, int resolucionInterior) {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		setParameters(radioExterno, radioInterno, resolucionExterior, resolucionInterior);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	~Toroide_dona() {

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
	void setOuterRadius(float radioExterno) {
		setParameters(radioExterno, radioInterno, resolucionExterior, resolucionInterior);
	}
	void setInnerRadius(float radioInterno) {
		setParameters(radioExterno, radioInterno, resolucionExterior, resolucionInterior);
	}
	void setOuterResolution(int resolucionExterior) {
		setParameters(radioExterno, radioInterno, resolucionExterior, resolucionInterior);
	}
	void setInnerResolution(int resolucionInterior) {
		setParameters(radioExterno, radioInterno, resolucionExterior, resolucionInterior);
	}
	void setParameters(float radioExterno, float radioInterno, int resolucionExterior, int resolucionInterior) {

		data.clear();
        float du = 2 * M_PI / resolucionExterior;
        float dv = 2 * M_PI / resolucionInterior;

        for (size_t i = 0; i < resolucionExterior; i++) {

            float u = i * du;

            for (size_t j = 0; j <= resolucionInterior; j++) {

                float v = (j % resolucionInterior) * dv;

                for (size_t k = 0; k < 2; k++)
                {
                    float uu = u + k * du;
    
                    float x = (radioExterno + radioInterno * cos(v)) * cos(uu);
                    float y = (radioExterno + radioInterno * cos(v)) * sin(uu);
                    float z = radioInterno * sin(v);

         
                    data.push_back(x);
                    data.push_back(y);
                    data.push_back(z);


                    float tx = uu / (2 * M_PI);
                    float ty = v / (2 * M_PI);


                    data.push_back(tx);
                    data.push_back(ty);
                }
          
                v += dv;
            }
        }
		
	}
};

#endif

