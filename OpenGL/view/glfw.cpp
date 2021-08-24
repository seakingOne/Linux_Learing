//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//// �Զ�����ɫ��
//#include "shader.h"
//
//// ��ȡͼƬ�ļ���
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//// ���Σ���������
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <iostream>
//
////��ǰ֡����һ֡��ʱ���
//float deltaTime = 0.0f;
////��һ֡��ʱ��
//float lastFrameTime = 0.0f;
//
////���λ��
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
////��Եķ���,�����Ϊ�߶ȸ��Ĺۿ��ģ���ʵ���ǵ�λ�ٶ�
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
////ͷ���ķ���
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// 
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow* window)
//{
//	glm::mat4 trans1 = glm::mat4(1.0f);
//	trans1 = glm::translate(trans1, glm::vec3(1.0f, 1.0f, 0.0f));
//
//	float cameraSpeed = 2.5f * deltaTime;
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	} 
//	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//		//��ʾ����ͷ��ǰƽ��
//		cameraPos += cameraSpeed * cameraFront;
//	}
//	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//		//��ʾ����ͷ���ƽ��
//		cameraPos -= cameraSpeed * cameraFront;
//	}
//	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//		//��ʾ����ͷ����ƽ��
//		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//	}
//	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//		//��ʾ����ͷ����ƽ��
//		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//	}
//}
//
//float lastX = 400;
//float lastY = 300;
//
////ƫ������ʼ��Ϊ-90.0�ȣ���Ϊƫ��0.0�ᵼ��ָ���ұߵķ���ʸ�����������������������תһ��
//float yaw = -90.0f;
//float pitch;
//
//float fov = 45.0f;//��Ұ����
//
//bool firstMouse = true;
//void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//	lastX = xpos;
//	lastY = ypos;
//
//	float sensitivity = 0.1f; // change this value to your liking
//	xoffset *= sensitivity;
//	yoffset *= sensitivity;
//
//	yaw += xoffset;
//	pitch += yoffset;
//
//	// make sure that when pitch is out of bounds, screen doesn't get flipped
//	if (pitch > 89.0f)
//		pitch = 89.0f;
//	if (pitch < -89.0f)
//		pitch = -89.0f;
//
//	glm::vec3 front;
//	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//	front.y = sin(glm::radians(pitch));
//	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//	cameraFront = glm::normalize(front);
//}
//
//// ÿ���������ֹ���ʱ���ͻ��������ص�����
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	fov -= (float)yoffset;
//	if (fov < 1.0f)
//		fov = 1.0f;
//	if (fov > 45.0f)
//		fov = 45.0f;
//}
//
//int main2()
//{
//	//����glfwInit��������ʼ��GLFW
//	glfwInit();
//
//	//ʹ��glfwWindowHint����������GLFW��glfwWindowHint�����ĵ�һ����������ѡ������ƣ�
//	//���ǿ��ԴӺܶ���GLFW_��ͷ��ö��ֵ��ѡ�񣻵ڶ�����������һ�����ͣ������������ѡ���ֵ
//	//�̶̳��ǻ���OpenGL 3.3�汾չ�����۵ģ�����������Ҫ����GLFW����Ҫʹ�õ�OpenGL�汾��3.3
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	//ͬ����ȷ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	//�������ڶ���
//	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	//glfwMakeContextCurrent(window);
//
//	//ָ�����ڵ�OpenGL��OpenGL ES�������ڵ����߳��ϴ��ڵ�ǰ״̬��һ��������һ��ֻ����һ���߳����ǵ�ǰ�ģ�ÿ���߳�һ��ֻ����һ����ǰ������
//	glfwMakeContextCurrent(window);
//	//����ָ�����ڵ�framebuffer resize�ص���������ָ�����ڵ�framebuffer���µ�����Сʱ���øûص�������
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	//ʹ�ûص�
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// ץȡ���
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	//GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ�����GLFW�����ǵ���glfwGetProcAddress�����������Ǳ����ϵͳ��������ȷ�ĺ���
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// ������Ȳ���
//	glEnable(GL_DEPTH_TEST);
//
//	Shader myShader("shader.vs", "shader.fs");
//
//	//3D �����嶥��
//	float vertices[] = {
//		// ��������            // ��������
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//	};
//
//	//��������������
//	glm::vec3 cubePositions[] = {
//		  glm::vec3(0.0f,  0.0f,  0.0f),
//		  glm::vec3(2.0f,  5.0f, -15.0f),
//		  glm::vec3(-1.5f, -2.2f, -2.5f),
//		  glm::vec3(-3.8f, -2.0f, -12.3f),
//		  glm::vec3(2.4f, -0.4f, -3.5f),
//		  glm::vec3(-1.7f,  3.0f, -7.5f),
//		  glm::vec3(1.3f, -2.0f, -2.5f),
//		  glm::vec3(1.5f,  2.0f, -2.5f),
//		  glm::vec3(1.5f,  0.2f, -1.5f),
//		  glm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//
//
//	//���Ȱ󶨶����������Ȼ��󶨺����ö��㻺������Ȼ�����ö�������
//	unsigned int VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	
//	glBindVertexArray(VAO);
//
//	//���ƶ������鵽�����й�OpenGLʹ��
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	// λ������
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	//��������
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	//��������
//	unsigned int texture, texture2;
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//
//	//����������װ����
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//�����������˲���
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	int width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true);
//	unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	stbi_image_free(data);
//
//	// ��2��������Ԫ
//	// ---------
//	glGenTextures(1, &texture2);
//	glBindTexture(GL_TEXTURE_2D, texture2);
//	// set the texture wrapping parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	// set texture filtering parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	// load image, create texture and generate mipmaps
//	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	stbi_image_free(data);
//
//	myShader.use();
//	myShader.setInt("texture1", 0);
//	myShader.setInt("texture2", 1);
//
//	// ���������������ر���֮ǰ���ϻ���ͼ���ܹ������û�����
//	while (!glfwWindowShouldClose(window))
//	{
//		// input
//		processInput(window);
//
//		//��¼deltaTime
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrameTime;
//		lastFrameTime = currentFrame;
//
//		// render
//		// ------
//		//glClearColor�����������Ļ���õ���ɫ
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		//������glClear�����������ɫ����֮��������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ
//		//glClear(GL_COLOR_BUFFER_BIT);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// bind Texture
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//
//		// ��������Ⱦһ������ʱҪʹ����ɫ������
//		myShader.use();
//
//		// 3DЧ��
//		glm::mat4 model = glm::mat4(1.0f);
//		glm::mat4 view = glm::mat4(1.0f);
//		glm::mat4 projection = glm::mat4(1.0f);
//		// �任
//		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
//		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//		
//		// ������Ƕȣ�Ҳ�����޸�view����
//		/*float radius = 10.0f;
//		float camX = sin(glfwGetTime()) * radius;
//		float camZ = cos(glfwGetTime()) * radius;*/
//		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//		
//		projection = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);
//
//		myShader.setMat4("projection", projection);
//		//myShader.setMat4("model", model);
//		myShader.setMat4("view", view);
//
//		// render boxes
//		//glBindVertexArray(VAO);
//		for (unsigned int i = 0; i < 10; i++)
//		{
//			// calculate the model matrix for each object and pass it to shader before drawing
//			glm::mat4 model = glm::mat4(1.0f);
//			model = glm::translate(model, cubePositions[i]);
//			float angle = 20.0f * i;
//			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//			myShader.setMat4("model", model);
//
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//
//		// glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�� -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		// glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
//		glfwPollEvents();
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	//glDeleteProgram(shaderProgram);
//
//	// glfw: terminate, clearing all previously allocated GLFW resources.
//	// ------------------------------------------------------------------
//	glfwTerminate();
//
//	return 0;
//
//}