#pragma once
#include <windows.h>
#include "Renderer.h"

class Window
{
public:
	HDC m_Hdc;
	HWND m_Hwnd;
	HGLRC m_Hrc;

	Window(HINSTANCE handle);
	~Window();

	void CreateOpenGLContext();
	void SetUpForRendering();
	void Run();

	long long milliseconds_now();

	// Custom Window Procedure
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	const char* CLASS_NAME = "Main Window Class";

	HINSTANCE m_Handle;

	Renderer m_Renderer;
	FrameBuffer m_DrawFrame;
	FrameBuffer m_ReadFrame;
};