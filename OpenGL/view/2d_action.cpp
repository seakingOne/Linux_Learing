#include "2d_action.h"

#include "window.h"
#include "vertex.h"
#include "texture.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int action() {

	// ��������
	GLFWwindow* window = create_window();

	// ������ɫ��
	Shader shader("shader-2d.vs", "shader-2d.fs");

	// ��ʼ���������ݣ��������ꡢ��ɫ���������꣩
	//float* vertices = getVertex_2d_data();
	float vertices[] = {
		// ��������            // ��������
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.0f,  1.0f, 1.0f,
		 -0.5f,  0.5f, -0.0f,  0.0f, 1.0f,
	};
	//unsigned int *indices = getIndices();
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	//�󶨶������ݣ�VBO:���㻺������VAO:�����������EBO:Ԫ�ػ������
	unsigned int VBO, VAO, EBO;
	//ָ��һ�����飬���д洢���ɵĶ����������, 1��ʾֻ����һ���������
	glGenVertexArrays(1, &VAO);
	//ָ��Ҫ�󶨵Ķ������������
	glBindVertexArray(VAO);

	//ָ��һ�����飬���д洢���ɵĻ���������
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//��������ʼ�������������ݴ洢
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//���ö�����������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// ����������������
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	// ��������Ԫͼ������
	unsigned int texture1 = create_texture_unit("wall.jpg", false);
	unsigned int texture2 = create_texture_unit("awesomeface.png", true);

	// ��ʼ����ɫ��������Դ����
	shader.use();
	//��������Ԫ
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	//ֻҪ���ڲ��رվ���Ҫ��Ⱦ
	while (!glfwWindowShouldClose(window))
	{

		//glClearColor�����������Ļ���õ���ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//������glClear�����������ɫ����֮��������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT);

		//������Ԫ
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		shader.use();

		//��ɫ������������ɫ���ϵ����set����ת�任�ȣ�
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)800 / 600, 0.1f, 100.0f);

		shader.setMat4("projection", projection);
		shader.setMat4("model", model);
		shader.setMat4("view", view);

		//��ȾWindow
		glBindVertexArray(VBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		//��ȡ�¼�
		glfwPollEvents();

	}

	//�ر�
	//�ͷŶ�������
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//�رմ���
	glfwTerminate();

	return 0;
}