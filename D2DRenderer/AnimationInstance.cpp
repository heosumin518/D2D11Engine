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

	// �ð� ������Ű�� // �ִϸ��̼� ��� �ð� ���� ��Ű��
	// ���� �ð����� ������ �ε��� ������Ű��
	if (mAnimationProgress > frameDistance)
	{
		/// �ڵ� �߰� �ʿ�

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

