#include "RunningMan.h"
#include "WinApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	assignment2::RunningMan runningMan(1578, 650, L"RuningMan");
	return gameProcessor::WinApp::Run(&runningMan, hInstance, nCmdShow);
}