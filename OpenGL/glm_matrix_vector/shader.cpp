#include "shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
	
	string vertexCode;
	string fragmentCode;
	ifstream vshaderFile;
	ifstream fShaderFile;

	unsigned int vertex;
	unsigned int fragment;

	try
	{
		// ���ļ���ת����
		vshaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShardeStream, fShardeStream;
		vShardeStream << vshaderFile.rdbuf();
		fShardeStream << fShaderFile.rdbuf();

		//�ر��ļ�
		vshaderFile.close();
		fShaderFile.close();

		// ת��Ϊstring
		vertexCode = vShardeStream.str();
		fragmentCode = fShardeStream.str();

	}
	catch (const std::exception&)
	{
		cout << "ERROR: file read fail" << endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* vfhaderCode = fragmentCode.c_str();

	// �������
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompilerErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &vfhaderCode, NULL);
	glCompileShader(fragment);
	checkCompilerErrors(fragment, "FRAGMENT");

	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	checkCompilerErrors(id, "PROGRAM");

	//ɾ����ɫ��
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}
void Shader::Shader::setBool(const string& name, bool value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::Shader::setInt(const string& name, int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::Shader::setFloat(const string& name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), (float)value);
}

void Shader::Shader::checkCompilerErrors(unsigned int shader, string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			cout << "ERROR: Compiltion error, type:" << type << endl;
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				cout << "ERROR: program error, type:" << type << endl;
			}
		}
	}
}

void Shader::Shader::use() {
	glUseProgram(id);
}

Shader::~Shader() {
	glDeleteProgram(id);
}
