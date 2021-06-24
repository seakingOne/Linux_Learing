#include "vertex.h"

float* getVertex_2d_data() {

	float vertices[] = {
		// 顶点坐标            // 纹理坐标
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.0f,  1.0f, 1.0f,
		 -0.5f,  0.5f, -0.0f,  0.0f, 1.0f,
	};

	return vertices;

}

unsigned int* getIndices() {

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	return indices;

}