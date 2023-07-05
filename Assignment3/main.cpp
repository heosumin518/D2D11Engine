#include "SolarSystem.h"
#include "WinApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	assignment3::SolarSystem solarSystem(1920, 1080, L"SolarSystem");
	return gameProcessor::WinApp::Run(&solarSystem, hInstance, nCmdShow);
}