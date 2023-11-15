#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stbi_image.h"

void Texture::Bind(GLint n)
{
	if (n == 0)
	{
		glBindTexture(m_Target, 0);
	}
	else
	{
		glBindTexture(m_Target, m_ID);

	}

	//glBindSampler(0, m_Sampler);
}

void Texture::SetTarget(const GLenum target)
{
	m_Target = target;
}

void Texture::SetData(const char * filename)
{
	stbi_set_flip_vertically_on_load(true);
	m_Data = stbi_load(filename, &m_Width, &m_Height, &m_Channels, 3);

	glTexStorage2D(m_Target, 0, GL_RGB, m_Width, m_Height);
	glTexSubImage2D(
		m_Target,
		0, 
		0, 0,
		m_Width,
		m_Height,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		m_Data
	);

	stbi_image_free(m_Data);
}

void Texture::Update(unsigned int render_program)
{
	int sampler_location = glGetUniformLocation(render_program, "TexMap");
	glUniform1i(sampler_location, 0);
}


Texture::~Texture() {

	if (glIsTexture(m_ID))
	{
		glDeleteTextures(1, &m_ID);
	}
}