#include "Mesh.h"


void Mesh::LoadMeshData(const Mesh& mesh)
{
	this->m_Data = mesh.m_Data;
	m_Data.shrink_to_fit();
	this->num_vertices = m_Data.size() / 4;
}

void Mesh::LoadMeshData(const char* filepath)
{
	// Do some file stuff here late
}

void Mesh::LoadMeshData(std::vector<float> & data, std::vector<unsigned int> & ind)
{
	m_Data = data;
	m_Data.shrink_to_fit();
	m_indices = ind;
	m_indices.shrink_to_fit();
	this->num_vertices = m_Data.size()/4;
	this->num_indices = m_indices.size();
}

void Mesh::Transform(glm::mat2& transform, float ts)
{
	int stride = 4;
	for (int index = 0; index < m_Data.size(); index += stride)
	{
		glm::vec2 pos(m_Data[index], m_Data[index + 1]);
		glm::vec2 new_pos = glm::normalize(transform * pos) * ts;
		glm::vec2 normalized = glm::normalize(pos/2.0f + new_pos/2.0f);
		//m_Data[index] = new_pos[0];
		//m_Data[index+1] = new_pos[1];
		//m_Data[index] = (pos[0] + new_pos[0]/2.0f);
		//m_Data[index+1] = (pos[1] + new_pos[1]/2.0f);
		m_Data[index] = normalized[0];
		m_Data[index + 1] = normalized[1];

	}
}
