// Rocket Launch Simulator.cpp : Defines the entry point for the application.
//

#include "Rocket Launch Simulator.h"

int wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    Window MainWindow(hInstance);
    MainWindow.Run();
    return 0;
}