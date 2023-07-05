#include "AnimationInstance.h"


AnimationInstance::AnimationInstance(unsigned int _frameIndex, unsigned int _animationIndex, D2D1_RECT_F _positionInfo, const AnimationAsset& _animationAsset)
	: mFrameIndex(_frameIndex)
	, mAnimationIndex(_animationIndex)
	, mAnimationProgress(0.f)
	, mPositionInfo(_positionInfo)
	, mAnimationAsset(_animationAsset)
{
}

void AnimationInstance::Update(float deltaTime)
{
	const std::vector<std::vector<FrameInfo>>& bitmapInfo = mAnimationAsset.GetBitmapInfo();
	float frameDistance = mAnimationAsset.GetFrameDistance();

	// 시간 누적시키기 // 애니메이션 경과 시간 증가 시키기
	// 일정 시간마다 프레임 인덱스 증가시키기
	if (mAnimationProgress > frameDistance)
	{
		/// 코드 추가 필요

		mAnimationProgress -= frameDistance;
		mFrameIndex++;
		if (mFrameIndex >= bitmapInfo[mAnimationIndex].size())
			mFrameIndex = 0;
	}
	mAnimationProgress += deltaTime;
}

void AnimationInstance::Render(ID2D1RenderTarget* renderTarget)
{
	ID2D1Bitmap* bitmap = mAnimationAsset.GetBitmap();
	const std::vector<std::vector<FrameInfo>>& bitmapInfo = mAnimationAsset.GetBitmapInfo();

	D2D1_RECT_F rect;
	rect.left = bitmapInfo[mAnimationIndex][mFrameIndex].left;
	rect.bottom = bitmapInfo[mAnimationIndex][mFrameIndex].bottom;
	rect.right = bitmapInfo[mAnimationIndex][mFrameIndex].right;
	rect.top = bitmapInfo[mAnimationIndex][mFrameIndex].top;
	renderTarget->DrawBitmap(bitmap, mPositionInfo, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect);
}

