#include "RunningMan.h"
#include "D2DRenderer.h"

namespace assignment2
{
	RunningMan::RunningMan(UINT width, UINT height, std::wstring name)
		: gameProcessor::GameProcessor(width, height, name)
		, mD2dRenderer(nullptr)
	{
	}

	bool RunningMan::Init()
	{
		mD2dRenderer = new D2DRenderer;
		mD2dRenderer->Initialize();

		return false;
	}

	void RunningMan::Update()
	{
	}

	void RunningMan::Render()
	{

	}
	void RunningMan::Destroy()
	{

	}
}