#include "DemoApp.h"
#include "D2DRenderer.h"

namespace assignment1
{
	DemoApp::DemoApp(UINT width, UINT height, std::wstring name)
		: gameProcessor::GameProcessor(width, height, name)
		, mD2dRenderer(nullptr)
	{
	}

	bool DemoApp::Init()
	{
		mD2dRenderer = new D2DRenderer;
		mD2dRenderer->Initialize();

		return true;
	}

	void DemoApp::Update()
	{

	}

	void DemoApp::Render()
	{
		mD2dRenderer->BeginDraw();
		mD2dRenderer->DrawRectangle({ 0, 0, 100, 100 }, D2D1::Matrix3x2F::Identity());
		mD2dRenderer->EndDraw();
	}

	void DemoApp::Destroy()
	{

	}

}