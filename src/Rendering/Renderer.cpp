#include "Renderer.h"
int Renderer::i = 0; // Initialize to 1;
unsigned int Renderer::offset1 = 0;
unsigned int Renderer::offset2 = 0;

Renderer::~Renderer()
{
}

void Renderer::AttachShader(Shader& shader)
{
    m_ActiveShaders.push_back(shader);
    glAttachShader(m_RenderProgram, shader.GetID());
}

void Renderer::CreateImage()
{
    GLenum flags = GL_COLOR_BUFFER_BIT;
    glClear(flags);
    glUseProgram(m_RenderProgram);
    for (auto& tex : m_Textures)
    {
        tex.Bind(1);
    }
    glDrawBuffer(GL_COLOR_ATTACHMENT0); // Front and back not allowed..
       
    //glDrawArrays(GL_TRIANGLES, 0, m_NumVertices);


    // Textures
    for (auto& tex : m_Textures)
    {
        glActiveTexture(GL_TEXTURE0);
        tex.Bind(1);
    }
    glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, NULL);
}

void Renderer::CreateProgram()
{
    m_RenderProgram = glCreateProgram();
}

void Renderer::Render(const FrameBuffer& drawframe)
{
    int x = (int)m_SceneCamera.m_Pos[0];
    int y = (int)m_SceneCamera.m_Pos[1];
    int width = m_SceneCamera.GetWidth();
    int height = m_SceneCamera.GetHeight();
    glViewport(x, y, width, height);

    glBlitFramebuffer(x, y, width, height,x,y, drawframe.m_Width, drawframe.m_Height, drawframe.flags, GL_LINEAR);
    
}

void Renderer::Run(FrameBuffer& drawframe)
{
    Render(drawframe);
    glFlush();
}

void Renderer::Init()
{
    glGenVertexArrays(1, &m_Vao);
    glBindVertexArray(m_Vao);

    glLinkProgram(m_RenderProgram);

    glUseProgram(m_RenderProgram);

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

    glGenBuffers(1, &m_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

    int max_num_obj = 500;

    GLuint size1 = sizeof(float) * max_num_obj * 4;
    GLuint size2 = sizeof(unsigned int) * max_num_obj;

    glBufferData(GL_ARRAY_BUFFER, size1, 0, GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size2, 0, GL_DYNAMIC_DRAW);
}

void Renderer::EnableAttribute(const char* attribute_name, unsigned int size)
{
    int location = glGetAttribLocation(m_RenderProgram, attribute_name);
    unsigned int stride = sizeof(float) * size * 2;
    unsigned int offset = stride * location;
    switch (location)
    {
    case -1:
        // Something Wrong happened
        break;
    case 0:
        offset = 0;
        break;
    case 1:
        offset = sizeof(float) * size * location;
        break;
    }
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
    glEnableVertexArrayAttrib(m_RenderProgram, location);

}

void Renderer::EnableUniform(const char* uniform_name, int size)
{
    int location = glGetUniformLocation(m_RenderProgram, uniform_name);
    m_ActiveUniforms.insert({ uniform_name, size });

}

void Renderer::LoadTextures(std::vector<Texture> textures)
{
    for (auto& i : textures)
    {
        m_Textures.push_back(i);
    }

    textures.shrink_to_fit();
    NumTex = textures.size();
}

void Renderer::Update(float ts)
{
    // To Do, Add relavent code here when needed.
    m_SceneCamera.Update(ts);

    // UPLOAD DATA TO OPENGL

    for (auto& i : m_MeshData)
    {
        int index = &i - &m_MeshData[0];

        int new_vertices = i.num_vertices;
        int new_indices = i.num_indices;
        // Keep track of the buffer size
        // Make sure to properly offset the data

        GLuint size1 = sizeof(float) * 4 * new_vertices;
        GLuint size2 = sizeof(unsigned int) * new_indices;

        // YOU HAVE THE INDEX IN THE ARRAY
        // YOU ALSO HAVE THE NUMBER OF ALL THE ELEMENTS IN THE ARRAY
        // YOU KNOW WHERE YOU ARE CURRENT LOOKING IN THE ARRAY
        // YOU HAVE TO FIND OUT HOW MANY MESHES IN THE ARRAY COME BEFORE ME, THAT IS GIVEN BY INDEX,
        // FIND OUT THE ACCUMULATIVE SIZE OF THE PRIOR DATA
        GLuint offset1 = 0;
        GLuint offset2 = 0;

        for (int i = 0; i < index; i++)
        {
            offset1 += sizeof(float) * 4 * m_MeshData[index - 1].num_vertices;
            offset2 += sizeof(unsigned int) * m_MeshData[index - 1].num_indices;
        }
        glBufferSubData(GL_ARRAY_BUFFER, offset1, size1, (void*)i.GetData());
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset2, size2, (void*)i.GetIndices());


        // TRANSFORMATIONS MAYBE
        glm::mat2 tr = m_ActiveTransforms[index];
        i.Transform(tr, ts);


        // Textures
        for (auto& tex : m_Textures)
        {
            tex.Update(m_RenderProgram);
        }


    }
    

    float pos[3] = { m_SceneCamera.m_Pos[0], m_SceneCamera.m_Pos[1], m_SceneCamera.m_Pos[2]};
    float pos_2[2] = { m_SceneCamera.m_Pos[0], m_SceneCamera.m_Pos[1] };
    
    for (auto& i : m_Textures)
    {
        i.Update(m_RenderProgram);
    }

    //for (auto& i : m_ActiveTransforms)
    //{
        int location = glGetUniformLocation(m_RenderProgram, "transform");
        glm::mat2 transform1({ {1.0f, 0.0f},{0.0f, 1.0f} });
        glm::mat2x2 I(2.0f);
        glUniformMatrix2fv(location, 4, GL_FALSE, glm::value_ptr(transform1));

    //}
    //float transform[4] = { 1.0, 0.0, 0.0,1.0 };

    for (auto& i : m_ActiveUniforms)
    {
        int location = glGetUniformLocation(m_RenderProgram, i.first);
        switch (i.second)
        {
        case 1:
            glUniform1f(location, ts);
            break;
        case 2:
            glUniform2fv(location, 2, pos_2);
            break;

        case 3:
            glUniform3fv(location, 3, pos);
            break;

        case 4:
            // Matrix
            //glUniformMatrix2fv(location, 4, GL_FALSE, glm::value_ptr(m_ActiveTransforms.at(0)));
            break;
        }
        
    }

    m_SceneCamera.Move(glm::vec3(10, 0, 0));
}

void Renderer::LoadData(Mesh& mesh, glm::mat2& transform)
{
    int new_vertices = mesh.num_vertices;
    int new_indices = mesh.num_indices;
    int link = m_NumIndices == 0 ? 0 : 4 * i;
    mesh.LinkIndices(link);
    m_NumVertices += new_vertices;
    m_NumIndices += new_indices;
    
    i++;
    m_MeshData.push_back(mesh);
    m_ActiveTransforms.push_back(transform);
}
