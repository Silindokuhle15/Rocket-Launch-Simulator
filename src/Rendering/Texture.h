#pragma once

#include "GL/glew.h"
#include "GL/wglew.h"

class Texture
{
public:
	Texture(GLenum target = GL_TEXTURE_2D) :m_Target{ target } {

		glGenTextures(1, &m_ID);

		glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glCreateSamplers(1, &m_Sampler);

		glSamplerParameteri(m_Sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glSamplerParameteri(m_Sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glGenerateMipmap(m_Target);

	}
	Texture(const char* filename,  GLenum target = GL_TEXTURE_2D) : 
		m_Target{ target } 
	{
		glGenTextures(1, &m_ID);

		glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glCreateSamplers(1, &m_Sampler);

		glSamplerParameteri(m_Sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glSamplerParameteri(m_Sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glGenerateMipmap(m_Target);
		//glGenTextures(1, &m_ID);
		this->Bind();
		this->SetData(filename);
	}

	~Texture();

	void Bind(GLint n = 0);
	unsigned char* GetData() const { return m_Data; }
	GLint GetWidth() const { return m_Width; }
	GLint GetHeight() const { return m_Height; }
	void SetTarget(const GLenum target);
	void SetData(const char* filename);
	void Update(unsigned int render_program);

private:

	GLuint m_ID;
	GLenum m_Target;
	GLuint m_Sampler;

	GLint m_Width;
	GLint m_Height;
	GLint m_Channels;

	unsigned char* m_Data;
};