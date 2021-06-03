#pragma once
#ifndef SHADER_H
#define SHADER_Hs

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader {

public:
	//程序id
	unsigned int id;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	//使用/激活程序
	void use();

	//uniform工具函数
	void setBool(const string &name, bool value) const;
	void setInt(const string &name, int value) const;
	void setFloat(const string &name, float value) const;
	~Shader();
private:
	void checkCompilerErrors(unsigned int shader, string type);
};

#endif // !SHADER_H

