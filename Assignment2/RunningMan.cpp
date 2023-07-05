#include "RunningMan.h"
#include "D2DRenderer.h"

#include <vector>

#include "FrameInfo.h"

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

		std::vector<std::vector<FrameInfo>> playerBitmapInfo = 
		{
			{
				{ 28, 36, 103, 84},
				{148, 36,  86, 84},
				{255, 34,  87, 86},
				{363, 32,  76, 88},
				{458, 31,  91, 89},
				{567, 40, 103, 80}
			}
		};

		std::vector<std::vector<FrameInfo>> backgroundBitmapInfo =
		{
			{
				{  0,   0, 789, 325},
				{789,   0, 789, 325},
				{  0, 325, 789, 325},
				{789, 325, 789, 325},
			}
		};

		D2D1_RECT_F bitmapPos1 = { 0, 0, 100, 100 };
		D2D1_RECT_F bitmapPos2 = { 100, 100, 200, 200 };
		D2D1_RECT_F bitmapPos3 = { 200, 200, 300, 300 };
		D2D1_RECT_F bitmapPos4 = { 300, 300, 400, 400 };
		D2D1_RECT_F bitmapPos5 = { 400, 400, 500, 500 };
		D2D1_RECT_F backgroundPos = { 0, 0, 1578, 650 };






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
		delete mD2dRenderer;
		delete playerBitmap;
		delete backgroundBitmap;
	}
}