#include "DemoApp.h"
#include "WinApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	assignment1::DemoApp demoApp(1280, 720, L"DemoApp");
	return gameProcessor::WinApp::Run(&demoApp, hInstance, nCmdShow);
}