#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
ȡɫ����https://m.fontke.com/tool/rgb/db3e54/
		http://xiaohudie.net/RGB.html
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

//const GLchar* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 position;\n"
//"layout (location = 1) in vec3 color;\n"
//"out vec3 ourColor;\n"
//"void main()\n"
//"{\n"
//"gl_Position = vec4(position, 1.0);\n"
//"ourColor = color;\n"
//"}\0";
//const GLchar* fragmentShaderSource = "#version 330 core\n"
//"out vec4 color;\n"
//"uniform vec4 ourColor;\n"
//"void main()\n"
//"{\n"
//"color = ourColor;\n"
//"}\n\0";

// ��unifrom������ɫ
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0);\n"
"ourColor = color;\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor; \n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(ourColor, 1.0f);\n"
"}\n\0";

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

	// ��Ⱦһ��������
	// ������ɫ��
	// ��������ɫ��
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// ��ɫ��Դ��������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// ������ɫ��
	glCompileShader(vertexShader);
	// У����ɫ���Ƿ����ʧ��
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Ƭ����ɫ��
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//��ɫ���������(Shader Program Object)�Ƕ����ɫ���ϲ�֮������������ɵİ汾�����Ҫʹ�øղű������ɫ�����Ǳ������������(Link)Ϊһ����ɫ���������
	//Ȼ������Ⱦ�����ʱ�򼤻������ɫ�������Ѽ�����ɫ���������ɫ���������Ƿ�����Ⱦ���õ�ʱ��ʹ�á�
	unsigned int shaderProgram = glCreateProgram();
	//�󶨵�shaderProgram����
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//У��link�Ƿ�������
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	//�ڰ���ɫ���������ӵ���������Ժ󣬼ǵ�ɾ����ɫ���������ǲ�����Ҫ������ ���˾��ÿ������Ϊ�ƶ�����Ȩ
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ����������������
	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f, // left  
	//	 0.5f, -0.5f, 0.0f, // right 
	//	 0.0f,  0.5f, 0.0f  // top   
	//};
	//���ö������ݵ���ɫ
	GLfloat vertices[] = {
		// λ��              // ��ɫ
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	};


	//���Ȱ󶨶����������Ȼ��󶨺����ö��㻺������Ȼ�����ö�������
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	//���ƶ������鵽�����й�OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//���ö�������
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	//glEnableVertexAttribArray(0);

	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

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

		// ��������Ⱦһ������ʱҪʹ����ɫ������
		glUseProgram(shaderProgram);

		// Update the uniform color
		/*GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.2f, greenValue, 0.0f, 1.0f);*/

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�� -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		// glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

	return 0;

}