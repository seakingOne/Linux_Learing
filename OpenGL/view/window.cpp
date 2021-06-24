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

	//使用glfwWindowHint函数来配置GLFW。glfwWindowHint函数的第一个参数代表选项的名称，
	//我们可以从很多以GLFW_开头的枚举值中选择；第二个参数接受一个整型，用来设置这个选项的值
	//教程都是基于OpenGL 3.3版本展开讨论的，所以我们需要告诉GLFW我们要使用的OpenGL版本是3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//同样明确告诉GLFW我们使用的是核心模式(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(width, height, "OpenGL窗口", NULL, NULL);
	if (window == NULL)
	{
		cout << "Windows窗口创建失败" << endl;
		return NULL;
	}

	//指定窗口的OpenGL或OpenGL ES上下文在调用线程上处于当前状态。一个上下文一次只能在一个线程上是当前的，每个线程一次只能有一个当前上下文
	glfwMakeContextCurrent(window);

	//设置指定窗口的framebuffer resize回调函数，当指定窗口的framebuffer重新调整大小时调用该回调函数。
	glfwSetFramebufferSizeCallback(window, frame_size_callback);

	//GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数。GLFW给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		window = NULL;
		return window;
	}

	return window;

}