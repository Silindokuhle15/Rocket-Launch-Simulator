#include "GL/glew.h"
#include <fstream>
#include <string>
#include <map>

class Shader
{
public:

	unsigned int GetID() const { return m_ID; }

	Shader(const char* path, GLenum type): 
		m_Path{path},
		m_ShaderType{type}
	{
		LoadFromFile(m_Path, m_ShaderSource);
		m_ID = glCreateShader(m_ShaderType);
		const char* src = m_ShaderSource.c_str();
		glShaderSource(m_ID, 1, &src, NULL);
		glCompileShader(m_ID);
	}

	static void LoadFromFile(const char* filepath, std::string& shader_source);

	~Shader() {

	}

private:
	const char* m_Path;
	std::string m_ShaderSource;
	GLenum m_ShaderType;
	unsigned int m_ID;
};