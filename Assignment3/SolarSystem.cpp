#include "SolarSystem.h"
#include "D2DRenderer.h"
#include "GameObject.h"

namespace assignment3
{
	SolarSystem::SolarSystem(UINT width, UINT height, std::wstring name)
		: gameProcessor::GameProcessor(width, height, name)
		, mD2dRenderer(nullptr)
		, mSun(nullptr)
		/*, mEarth(nullptr)
		, mMoon(nullptr)*/
	{
	}

	bool SolarSystem::Init()
	{
		mD2dRenderer = new D2DRenderer;
		mD2dRenderer->Initialize();

		// GameObject(const D2D1_RECT_F & rectangle, const TransformInfo & transformInfo)

		TransformInfo transformInfo;
		transformInfo.ScaleX = 1.f;
		transformInfo.ScaleY = 1.f;
		transformInfo.Rotation = 2.f;
		transformInfo.MoveX = mWidth / 2;
		transformInfo.MoveY = mHeight / 2;
	/*	struct TransformInfo
		{
			float scaleX, scaleY;
			float rotation;
			float moveX, moveY;
		};

	*/
			
		mSun = new GameObject({ -100, -100, 100, 100 }, transformInfo);

		transformInfo.ScaleX = 0.5f;
		transformInfo.ScaleY = 0.5f;
		transformInfo.MoveX = 300.f;
		transformInfo.MoveY = 0.f;

		GameObject*  mEarth = new GameObject({ -100, -100, 100, 100 }, transformInfo);

		transformInfo.ScaleX = 0.5f;
		transformInfo.ScaleY = 0.5f;
		transformInfo.MoveX = 200.f;
		transformInfo.MoveY = 0.f;

		GameObject* mMoon = new GameObject({ -100, -100, 100, 100 }, transformInfo);

		mSun->AddChildGameObject(mEarth);
		mEarth->AddChildGameObject(mMoon);
		mEarth->SetParentGameObject(mSun);
		mMoon->SetParentGameObject(mEarth);

		return true;
	}

	void SolarSystem::Update()
	{
		mSun->Update();
		/*mEarth->Update();
		mMoon->Update();*/
	}

	void SolarSystem::Render()
	{
		mD2dRenderer->BeginDraw();



		//mD2dRenderer->DrawRectangle({ 0, 0, 100, 100 }, D2D1::Matrix3x2F::Identity());

		mSun->Render(mD2dRenderer);
		/*mEarth->Render(mD2dRenderer);
		mMoon->Render(mD2dRenderer);*/

		mD2dRenderer->EndDraw();
	}

	void SolarSystem::Destroy()
	{
		delete mD2dRenderer;
		delete mSun;/*
		delete mEarth;
		delete mMoon;*/
	}

}