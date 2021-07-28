#pragma once
#ifndef SHADER_H
#define SHADER_Hs

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader {

public:
	//����id
	unsigned int id;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	//ʹ��/�������
	void use();

	//uniform���ߺ���
	void setBool(const string &name, bool value) const;
	void setInt(const string &name, int value) const;
	void setFloat(const string &name, float value) const;
	void setMat4(const string& name, const glm::mat4& mat) const;
	
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;

	~Shader();
private:
	void checkCompilerErrors(unsigned int shader, string type);
};

#endif // !SHADER_H

