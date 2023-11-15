#pragma once
#include "GL/glew.h"
#include "GL/wglew.h"

class FrameBuffer
{

public:
	FrameBuffer(unsigned int target = GL_DRAW_BUFFER): 
		m_Width{1920},
		m_Height{1080},
		m_Format{GL_RGB},
		m_Type{GL_UNSIGNED_BYTE},
		m_FBO{0},
		m_FBO_target{target}
	{
	};

	~FrameBuffer()
	{
	};

	void Init();
	void SetTarget(unsigned int target);

	GLbitfield flags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	unsigned int m_Width;
	unsigned int m_Height;
	unsigned int m_Format;
	GLenum m_Type;
	unsigned int m_FBO;
	unsigned int m_FBO_target;
	unsigned int m_BufferData;

	unsigned char * m_Pixels;

};