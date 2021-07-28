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
		// 打开文件，转换流
		vshaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShardeStream, fShardeStream;
		vShardeStream << vshaderFile.rdbuf();
		fShardeStream << fShaderFile.rdbuf();

		//关闭文件
		vshaderFile.close();
		fShaderFile.close();

		// 转换为string
		vertexCode = vShardeStream.str();
		fragmentCode = fShardeStream.str();

	}
	catch (const std::exception&)
	{
		cout << "ERROR: file read fail" << endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* vfhaderCode = fragmentCode.c_str();

	// 编译代码
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

	//删除着色器
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

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void Shader::Shader::setMat4(const string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::Shader::use() {
	glUseProgram(id);
}

Shader::~Shader() {
	glDeleteProgram(id);
}
