#include "Window.h"
#include "resources.h"

LRESULT Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_QUIT:
        break;

    case WM_KEYDOWN:
        break;

    case WM_KEYUP:
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}


Window::Window(HINSTANCE hInstance)
{
    m_Handle = hInstance;

    // Register the window class.
    const char CLASS_NAME[] = "Sample Window Class";
    WNDCLASS wc = { };
    wc.lpfnWndProc = Window::WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

    RegisterClass(&wc);
    // Create the window.
    m_Hwnd = CreateWindowEx(
        0, // Optional window styles.
        CLASS_NAME, // Window class
        "Rocket Launch Simulator", // Window text
        WS_OVERLAPPEDWINDOW, // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080,
        NULL, // Parent window
        NULL, // Menu
        hInstance, // Instance handle
        NULL // Additional application data
    );
}

Window::~Window()
{

    //wglMakeCurrent(ourWindowHandleToDeviceContext, NULL); Unnecessary; wglDeleteContext will make the context not current
    //wglDeleteContext(ourOpenGLRenderingContext);
}


void Window::CreateOpenGLContext()
{    
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	m_Hdc = GetDC(m_Hwnd);

	int  letWindowsChooseThisPixelFormat;
	letWindowsChooseThisPixelFormat = ChoosePixelFormat(m_Hdc, &pfd);
	SetPixelFormat(m_Hdc, letWindowsChooseThisPixelFormat, &pfd);

	//HGLRC ourOpenGLRenderingContext = wglCreateContext(m_Hdc);
	//wglMakeCurrent(m_Hdc, ourOpenGLRenderingContext);

    HGLRC tempContext = wglCreateContext(m_Hdc);
    wglMakeCurrent(m_Hdc, tempContext);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        //AfxMessageBox(_T("GLEW is not initialized!"));
    }

    int attribs[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB, 0,
        0
    };

    if (wglewIsSupported("WGL_ARB_create_context") == 1)
    {
        m_Hrc = wglCreateContextAttribsARB(m_Hdc, 0, attribs);
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(tempContext);
        wglMakeCurrent(m_Hdc, m_Hrc);
    }
    else
    {	//It's not possible to make a GL 3.x context. Use the old style context (GL 2.1 and before)
        m_Hrc = tempContext;
    }
    //Checking GL version
    const GLubyte* GLVersionString = glGetString(GL_VERSION);

    //Or better yet, use the GL3 way to get the version number
    int OpenGLVersion[2];
    glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);

    MessageBoxA(0, (char*)glGetString(GL_VERSION), "OPENGL VERSION", 0);
}

void Window::SetUpForRendering()
{
    CreateOpenGLContext();
    m_DrawFrame.Init();
    m_ReadFrame.SetTarget(GL_READ_BUFFER);
    m_ReadFrame.Init();

    // create the mesh here and see
    Mesh mesh1;
    mesh1.LoadMeshData(rc::data1, rc::indices1);

    Mesh mesh2;
    mesh2.LoadMeshData(rc::data2, rc::indices2);

    Mesh mesh3;
    mesh3.LoadMeshData(rc::data3, rc::indices3);
    std::vector<Texture> textures;

    Mesh mesh4;
    mesh4.LoadMeshData(rc::data4, rc::indices1);

    for (auto& i : rc::filenames)
    {   
        textures.push_back(Texture(i));
    }

    glm::mat2 transform1(1.0f);
    glm::mat2 transform2(
        {-1.0f, +0.0f},
        {+0.0f, +1.0f}
        );
    glm::mat2 transform3(
        { +1.0f, 0.0f },
        { +0.0f, 1.0f}
        );

    glm::mat2 transform4(
        { +0.90f , +0.90f},
        { -0.90f , +0.90f}
        );

    const char* path1 = "C:/dev/Rocket Launch Simulator/assets/vShader.glsl"; // GL_VERTEX_SHADER
        
    const char* path2 = "C:/dev/Rocket Launch Simulator/assets/fShader.glsl"; // GL_FRAGMENT_SHADER
       
    m_Renderer.CreateProgram();

    Shader vshader(path1, GL_VERTEX_SHADER);
    Shader fshader(path2, GL_FRAGMENT_SHADER);
    m_Renderer.AttachShader(vshader);
    m_Renderer.AttachShader(fshader);
    m_Renderer.Init();
    m_Renderer.LoadTextures(textures);
    //m_Renderer.LoadData(mesh4, transform2);
    m_Renderer.LoadData(mesh4, transform3);
    //m_Renderer.LoadData(mesh3, transform1);
    //m_Renderer.LoadData(mesh4, transform2);
    m_Renderer.EnableAttribute("pos");
    m_Renderer.EnableAttribute("tex");

    m_Renderer.EnableUniform("cam_pos", 3);
    m_Renderer.EnableUniform("transform", 4);
    m_Renderer.EnableUniform("ts", 1);

}

void Window::Run()
{
    SetUpForRendering();
    ShowWindow(m_Hwnd, 10);
    // Run the message loop.
    MSG msg = { };

    while (true)
    {
        long long start = milliseconds_now();
        
        if (PeekMessage(&msg, m_Hwnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
         }

        m_Renderer.CreateImage();
        m_Renderer.Run(m_DrawFrame);

        long long elapsed = milliseconds_now() - start;
        float ts = elapsed/1000.0f;
        m_Renderer.Update(ts);

        SwapBuffers(m_Hdc);
    }    
}

long long Window::milliseconds_now() {
    static LARGE_INTEGER s_frequency;
    static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
    if (s_use_qpc) {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (1000LL * now.QuadPart) / s_frequency.QuadPart;
    }
    else {
        return GetTickCount64();
    }
}
