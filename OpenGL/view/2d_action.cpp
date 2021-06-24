#include "2d_action.h"

#include "window.h"
#include "vertex.h"
#include "texture.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int action() {

	// 创建窗口
	GLFWwindow* window = create_window();

	// 编译着色器
	Shader shader("shader-2d.vs", "shader-2d.fs");

	// 初始化顶点数据（顶点坐标、颜色、纹理坐标）
	//float* vertices = getVertex_2d_data();
	float vertices[] = {
		// 顶点坐标            // 纹理坐标
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

	//绑定顶点数据，VBO:顶点缓冲区，VAO:顶点数组对象，EBO:元素缓冲对象
	unsigned int VBO, VAO, EBO;
	//指定一个数组，其中存储生成的顶点数组对象, 1表示只生成一个数组对象
	glGenVertexArrays(1, &VAO);
	//指定要绑定的顶点数组的名称
	glBindVertexArray(VAO);

	//指定一个数组，其中存储生成的缓冲区对象
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//创建并初始化缓冲对象的数据存储
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//设置顶点属性数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// 设置纹理属性数据
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	// 加载纹理单元图像数据
	unsigned int texture1 = create_texture_unit("wall.jpg", false);
	unsigned int texture2 = create_texture_unit("awesomeface.png", true);

	// 初始化着色器，编译源代码
	shader.use();
	//设置纹理单元
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	//只要窗口不关闭就需要渲染
	while (!glfwWindowShouldClose(window))
	{

		//glClearColor来设置清空屏幕所用的颜色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色
		glClear(GL_COLOR_BUFFER_BIT);

		//绑定纹理单元
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		shader.use();

		//着色器处理（包括着色器上的入参set，旋转变换等）
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)800 / 600, 0.1f, 100.0f);

		shader.setMat4("projection", projection);
		shader.setMat4("model", model);
		shader.setMat4("view", view);

		//渲染Window
		glBindVertexArray(VBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		//拉取事件
		glfwPollEvents();

	}

	//关闭
	//释放顶点数据
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//关闭窗口
	glfwTerminate();

	return 0;
}