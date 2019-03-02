#pragma once
#include <gl/glew.h>
class Texture
{
private:
	unsigned int tex = 0;
public:
	Texture()
	{

	}
	Texture(unsigned int width, unsigned int height, unsigned char * data)
	{
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE, tex);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE, 0);
	}
	void Bind()
	{
		glBindTexture(GL_TEXTURE, tex);
	}
	void Unbind()
	{
		glBindTexture(GL_TEXTURE, 0);
	}
};