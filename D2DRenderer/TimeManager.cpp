#include "TimeManager.h"

TimeManager::TimeManager()
{
	Init();
}

void TimeManager::Init()
{
	QueryPerformanceFrequency(&mFrequency);		// 현재 카운트
	QueryPerformanceCounter(&mCurTime);			// 이전 카운트
	mPrevTime = mCurTime;
	mDeltaTime = 0.f;
	mFrameCount = 0;
	mFPS = 0;
}

void TimeManager::Update()
{
	static float sTime = 0.f;
	sTime += GetDeltaTime();

	if (sTime >= 1.f)
	{
		sTime -= 1.f;
		mFPS = mFrameCount;
		mFrameCount = 0;
	}

	mDeltaTime = static_cast<float>(mCurTime.QuadPart - mPrevTime.QuadPart) / mFrequency.QuadPart;
	mPrevTime = mCurTime;
	QueryPerformanceCounter(&mCurTime);
	++mFrameCount;
}