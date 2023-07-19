#include "CameraTest.h"
#include "WinApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	assignment4::CameraTest cameraTest(1280, 720, L"CameraTest");
	return gameProcessor::WinApp::Run(&cameraTest, hInstance, nCmdShow);
}