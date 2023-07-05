#include "AnimationAsset.h"


AnimationAsset::AnimationAsset(ID2D1Bitmap* _bitmap, const std::vector<std::vector<FrameInfo>>& _bitmapInfo, float _frameDistance)
	: mBitmap(_bitmap)
	, mFrameAnimationInfo(_bitmapInfo)
	, mFrameDistance(_frameDistance)
{
	mBitmap->AddRef();	// 참조 카운트++
}

AnimationAsset::~AnimationAsset()
{
	unsigned int count = mBitmap->Release();	// 참조 카운트--
}
