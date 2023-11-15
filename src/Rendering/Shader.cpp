#include "Shader.h"

void Shader::LoadFromFile(const char* filepath, std::string& shader_source)
{
    std::ifstream is;
    std::string file_data;

    is = std::ifstream(filepath);
    is.seekg(0, std::ios::end);
    file_data.reserve(is.tellg());
    is.seekg(0, std::ios::beg);
    file_data.assign(std::istreambuf_iterator<char>(is),
        std::istreambuf_iterator<char>());

    shader_source = file_data;
    //file_data.clear();
}
