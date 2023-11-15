#pragma once
#include "FrameBuffer.h"
#include "Texture.h"
#include "Mesh.h"
#include "Camera.h"
#include <map>
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/mat2x2.hpp"

class Renderer
{
public:

	GLuint m_Vao;
	GLuint m_VertexBuffer, m_IndexBuffer, m_RenderProgram;
	GLint m_NumVertices;
	GLint m_NumIndices;

	GLint NumTex;
	GLuint m_Sampler;

	static int i;
	static unsigned int offset1;
	static unsigned int offset2;

	Camera m_SceneCamera;

	char bitExtracted(char num, int k, int p)
	{
		return (((1 << k) - 1) & (num >> (p - 1)));
	}

	void AttachShader(Shader& shader);
	void CreateImage();
	void CreateProgram();
	void EnableAttribute(const char*, unsigned int size = 2);
	void EnableUniform(const char*, int size);
	void Init();
	void LoadData(Mesh& mesh, glm::mat2 & transform);
	void LoadTextures(std::vector<Texture> textures);
	void Render(const FrameBuffer& drawframe);
	void Run(FrameBuffer& drawBuffer);
	void Update(float ts);

	Renderer() : m_NumVertices{ 0 }, m_NumIndices {0} 
	{
	}
	~Renderer();

private:
	std::vector<Texture> m_Textures;
	std::map<const char*, int> m_ActiveUniforms;
	std::vector<glm::mat2> m_ActiveTransforms;
	std::vector<Shader> m_ActiveShaders;
	std::vector<Mesh> m_MeshData;

	
};