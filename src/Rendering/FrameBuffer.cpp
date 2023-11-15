#include "FrameBuffer.h"

void FrameBuffer::Init()
{
	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(m_FBO_target, m_FBO);
}

void FrameBuffer::SetTarget(unsigned int target)
{
	m_FBO_target = target;
}
