#include "Camera.h"

void Camera::Update(float ts)
{
	m_TimeStep = ts;
}

void Camera::Move(glm::vec3 dir)
{
	m_Pos += dir * m_TimeStep;
}

void Camera::ReCenter()
{
	m_Pos = glm::vec3(0);
}

void Camera::ReSize(const int w, const int h)
{
	m_Width = w;
	m_Height = h;
}
