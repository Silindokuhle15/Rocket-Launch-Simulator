#pragma once
#include "glm/common.hpp"
#include "glm/glm.hpp"

class Camera
{
public:
	// Declare public variables

	glm::vec3 m_Pos;
	glm::vec2 m_Velocity;

	// Public function declarations
	int GetHeight() const { return m_Height; }
	int GetWidth() const {	return m_Width; }
	void Move(glm::vec3 dir);
	void ReCenter();
	void ReSize(const int w, const int h);
	void Update(float ts);

	Camera() :
		m_Pos{0.0, 0.0, 10.f},
		m_Velocity{ 0 }
	{

	}


	Camera(glm::vec3 pos, glm::vec2 vel) :
		m_Pos{ pos },
		m_Velocity{vel}
	{
		m_TimeStep = 0.0f;
		m_Width = 1920;	// You can do better ... 
		m_Height = 1080; // Change this some time later too
	}

	~Camera() {}

private:

	float m_TimeStep;
	unsigned int m_Width;
	unsigned int m_Height;
};