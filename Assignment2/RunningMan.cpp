#include "RunningMan.h"
//#include "D2DRenderer.h"
//#include "AnimationAsset.h"
//#include "AnimationInstance.h"

//#include <vector>
#include <cassert>
//#include <map>

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

		D2D1_RECT_F playerBitmapPos1 = { 0, 0, 100, 100 };
		D2D1_RECT_F playerBitmapPos2 = { 100, 100, 200, 200 };
		D2D1_RECT_F playerBitmapPos3 = { 200, 200, 300, 300 };
		D2D1_RECT_F playerBitmapPos4 = { 300, 300, 400, 400 };
		D2D1_RECT_F playerBitmapPos5 = { 400, 400, 500, 500 };
		D2D1_RECT_F backgroundPos = { 0, 0, 1578, 650 };

		const WCHAR* playerPath = L"../Resource/run.png";
		const WCHAR* backgroundPath = L"../Resource/midnight.png";

		HRESULT hr = mD2dRenderer->CreateD2DBitmapFromFile(playerPath, &playerBitmap);
		assert(SUCCEEDED(hr));
		hr = mD2dRenderer->CreateD2DBitmapFromFile(backgroundPath, &backgroundBitmap);
		assert(SUCCEEDED(hr));
		
		mD2dRenderer->DrawBitmap(playerBitmap);
		mD2dRenderer->DrawBitmap(backgroundBitmap);

		animationAssets.insert({ playerPath ,new AnimationAsset(playerBitmap, playerBitmapInfo, 0.2f) });
		animationAssets.insert({ backgroundPath,new AnimationAsset(backgroundBitmap, backgroundBitmapInfo, 0.2f) });

		animationInstances.reserve(1024);

		auto playerIter = animationAssets.find(playerPath);
		assert(playerIter != animationAssets.end());
		auto backgroundIter = animationAssets.find(backgroundPath);
		assert(backgroundIter != animationAssets.end());

		mD2dRenderer->DrawBitmap(playerIter->second->GetBitmap());
		mD2dRenderer->DrawBitmap(backgroundIter->second->GetBitmap());

		animationInstances.push_back({ 0, 0, backgroundPos, *(backgroundIter->second) });
		animationInstances.push_back({ 0, 0, playerBitmapPos1, *(playerIter->second) });
		animationInstances.push_back({ 0, 0, playerBitmapPos2, *(playerIter->second) });
		animationInstances.push_back({ 0, 0, playerBitmapPos3, *(playerIter->second) });
		animationInstances.push_back({ 0, 0, playerBitmapPos4, *(playerIter->second) });
		animationInstances.push_back({ 0, 0, playerBitmapPos5, *(playerIter->second) });

		mD2dRenderer->DrawBitmap(playerIter->second->GetBitmap());
		mD2dRenderer->DrawBitmap(backgroundIter->second->GetBitmap());


		return false;
	}

	void RunningMan::Update()
	{
		for (auto& ani : animationInstances)
		{
			ani.Update(0.01f);
		}
	}

	void RunningMan::Render()
	{
		mD2dRenderer->BeginDraw();

		for (auto& ani : animationInstances)
		{
			ani.Render(mD2dRenderer);
		}

		mD2dRenderer->EndDraw();
	}
	void RunningMan::Destroy()
	{
		for (auto ani : animationAssets)
		{
			// AnimationAsset* temp = ani.second;   // 값이 잘 들어갔는지 확인용
			delete ani.second;
		}
		animationInstances.clear();

		backgroundBitmap->Release();
		playerBitmap->Release();

		delete mD2dRenderer;
	}
}