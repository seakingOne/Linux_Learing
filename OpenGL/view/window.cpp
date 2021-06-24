#include "window.h"
#include <iostream>

using namespace std;

int width = 800;
int height = 600;

void frame_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* create_window() {

	glfwInit();

	//ʹ��glfwWindowHint����������GLFW��glfwWindowHint�����ĵ�һ����������ѡ������ƣ�
	//���ǿ��ԴӺܶ���GLFW_��ͷ��ö��ֵ��ѡ�񣻵ڶ�����������һ�����ͣ������������ѡ���ֵ
	//�̶̳��ǻ���OpenGL 3.3�汾չ�����۵ģ�����������Ҫ����GLFW����Ҫʹ�õ�OpenGL�汾��3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//ͬ����ȷ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(width, height, "OpenGL����", NULL, NULL);
	if (window == NULL)
	{
		cout << "Windows���ڴ���ʧ��" << endl;
		return NULL;
	}

	//ָ�����ڵ�OpenGL��OpenGL ES�������ڵ����߳��ϴ��ڵ�ǰ״̬��һ��������һ��ֻ����һ���߳����ǵ�ǰ�ģ�ÿ���߳�һ��ֻ����һ����ǰ������
	glfwMakeContextCurrent(window);

	//����ָ�����ڵ�framebuffer resize�ص���������ָ�����ڵ�framebuffer���µ�����Сʱ���øûص�������
	glfwSetFramebufferSizeCallback(window, frame_size_callback);

	//GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ�����GLFW�����ǵ���glfwGetProcAddress�����������Ǳ����ϵͳ��������ȷ�ĺ���
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		window = NULL;
		return window;
	}

	return window;

}