#include "texture.h"

// ��ȡͼƬ�ļ���
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

using namespace std;

int create_texture_unit(const char* img_path, bool lucency) {

	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//���������װ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//����������˲���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//��ȡͼƬ
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(img_path, &width, &height, &nrChannels, 0);
	if (data)
	{

		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3 || lucency == true)
			format = GL_RGB;
		else if (nrChannels == 4 || lucency == false)
			format = GL_RGBA;

		//ָ��һ����ά����ͼ��, ����ͼƬ����͸����
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	return texture;

}