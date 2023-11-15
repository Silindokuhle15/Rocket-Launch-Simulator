#pragma once
#include <vector>
#include "glm/glm.hpp"

class Mesh
{
public:

	unsigned int num_vertices;
	unsigned int num_indices;

	const float* GetData() const {
		return m_Data.data();
	}

	const unsigned int* GetIndices() const {
		return m_indices.data();
	}
	std::vector<unsigned int> GetIndicesV() const
	{
		return m_indices;
	}
	void LinkIndices(unsigned int num) {
		for (auto& i : m_indices)
		{
			i += num;
		}
	}

	void LoadMeshData(const Mesh& mesh);
	void LoadMeshData(const char* filepath);
	void LoadMeshData(std::vector<float> &data, std::vector<unsigned int> & ind);

	void Transform(glm::mat2& transform, float ts);

	Mesh() {

	}
	~Mesh() {

	}
private:
	std::vector<unsigned int> m_indices;
	std::vector<float> m_Data;
};