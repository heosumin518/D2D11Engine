#include "AnimationAsset.h"


AnimationAsset::AnimationAsset(ID2D1Bitmap* _bitmap, const std::vector<std::vector<FrameInfo>>& _bitmapInfo, float _frameDistance)
	: mBitmap(_bitmap)
	, mFrameAnimationInfo(_bitmapInfo)
	, mFrameDistance(_frameDistance)
{
	mBitmap->AddRef();	// ���� ī��Ʈ++
}

AnimationAsset::~AnimationAsset()
{
	unsigned int count = mBitmap->Release();	// ���� ī��Ʈ--
}
