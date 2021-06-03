#include <glad/glad.h>
#include <GLFW/glfw3.h>

// �Զ�����ɫ��
#include "shader.h"

// ��ȡͼƬ�ļ���
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// ���Σ���������
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

/*
��OpenGL�У��κ����ﶼ��3D�ռ��У�����Ļ�ʹ���ȴ��2D�������飬�⵼��OpenGL�Ĵ󲿷ֹ������ǹ��ڰ�3D����ת��Ϊ��Ӧ����Ļ��2D���ء�
3D����תΪ2D����Ĵ����������OpenGL��ͼ����Ⱦ���ߣ�Graphics Pipeline�������Ϊ���ߣ�ʵ����ָ����һ��ԭʼͼ������;��һ�����͹ܵ���
�ڼ侭�����ֱ仯�������ճ�������Ļ�Ĺ��̣�����ġ�ͼ����Ⱦ���߿��Ա�����Ϊ������Ҫ���֣���һ���ְ����3D����ת��Ϊ2D���꣬
�ڶ������ǰ�2D����ת��Ϊʵ�ʵ�����ɫ�����ء�����̳�����ǻ�򵥵�����һ��ͼ����Ⱦ���ߣ��Լ��������������һЩƯ�������ء�


ͼ����Ⱦ���߽���һ��3D���꣬Ȼ�������ת��Ϊ����Ļ�ϵ���ɫ2D���������ͼ����Ⱦ���߿��Ա�����Ϊ�����׶Σ�ÿ���׶ν����ǰһ���׶ε������Ϊ���롣
������Щ�׶ζ��Ǹ߶�ר�Ż��ģ����Ƕ���һ���ض��ĺ����������Һ����ײ���ִ�С������������Ǿ��в���ִ�е����ԣ����������Կ����г�ǧ�����С������ģ�
������GPU��Ϊÿһ������Ⱦ���ߣ��׶����и��Ե�С���򣬴Ӷ���ͼ����Ⱦ�����п��ٴ���������ݡ���ЩС���������ɫ��(Shader)��

��Щ��ɫ�����������Լ����ã���������������Լ�д����ɫ�����滻Ĭ�ϵġ��������ǾͿ��Ը�ϸ�µؿ���ͼ����Ⱦ�����е��ض������ˣ�
������Ϊ����������GPU�ϣ��������ǿ��Ը����ǽ�Լ�����CPUʱ�䡣OpenGL��ɫ������OpenGL��ɫ������(OpenGL Shading Language, GLSL)д�ɵ�

link: https://learnopengl-cn.github.io/img/01/04/pipeline.png
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// 
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	//����glfwInit��������ʼ��GLFW
	glfwInit();

	//ʹ��glfwWindowHint����������GLFW��glfwWindowHint�����ĵ�һ����������ѡ������ƣ�
	//���ǿ��ԴӺܶ���GLFW_��ͷ��ö��ֵ��ѡ�񣻵ڶ�����������һ�����ͣ������������ѡ���ֵ
	//�̶̳��ǻ���OpenGL 3.3�汾չ�����۵ģ�����������Ҫ����GLFW����Ҫʹ�õ�OpenGL�汾��3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//ͬ����ȷ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//�������ڶ���
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//glfwMakeContextCurrent(window);

	//ָ�����ڵ�OpenGL��OpenGL ES�������ڵ����߳��ϴ��ڵ�ǰ״̬��һ��������һ��ֻ����һ���߳����ǵ�ǰ�ģ�ÿ���߳�һ��ֻ����һ����ǰ������
	glfwMakeContextCurrent(window);
	//����ָ�����ڵ�framebuffer resize�ص���������ָ�����ڵ�framebuffer���µ�����Сʱ���øûص�������
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ�����GLFW�����ǵ���glfwGetProcAddress�����������Ǳ����ϵͳ��������ȷ�ĺ���
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader myShader("shader.vs", "shader.fs");

	// ����������������
	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f, // left  
	//	 0.5f, -0.5f, 0.0f, // right 
	//	 0.0f,  0.5f, 0.0f  // top   
	//};
	////���ö������ݵ���ɫ
	//GLfloat vertices[] = {
	//	// λ��              // ��ɫ
	//	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
	//	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
	//	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	//};

	//���������������
	GLfloat vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
	};

	//���þ�������
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};


	//���Ȱ󶨶����������Ȼ��󶨺����ö��㻺������Ȼ�����ö�������
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);

	//���ƶ������鵽�����й�OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//index��������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//���ö�������
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	//glEnableVertexAttribArray(0);

	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//��������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//��������
	unsigned int texture, texture2;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//���������װ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//����������˲���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// ��2������Ԫ
	// ---------
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	myShader.use();
	glUniform1i(glGetUniformLocation(myShader.id, "texture"), 0);
	myShader.setInt("texture2", 1);

	// ���������������ر���֮ǰ���ϻ���ͼ���ܹ������û�����
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		//glClearColor�����������Ļ���õ���ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//������glClear�����������ɫ����֮��������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT);

		// bind Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// ��������Ⱦһ������ʱҪʹ����ɫ������
		myShader.use();

		// ͨ������������任�ڵ�λ��
		glm::mat4 trans(1.0f);
		//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		
		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		unsigned int transformLoc = glGetUniformLocation(myShader.id, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		// Update the uniform color
		/*GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.2f, greenValue, 0.0f, 1.0f);*/

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 4);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�� -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		// glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteProgram(shaderProgram);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

	return 0;

}