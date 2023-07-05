#pragma once
#include "AnimationAsset.h"
#include "D2DRenderer.h"

class AnimationInstance
{
public:
	AnimationInstance(unsigned int _frameIndex, unsigned int _animationIndex, D2D1_RECT_F _positionInfo, const AnimationAsset& _animationAsset); //float _animationProgress

	void Update(float deltaTime);
	void Render(D2DRenderer* d2dRenderer);	//ID2D1RenderTarget* renderTarget

private:
	/// ��Ʈ��
	// ��ǥ���� -> 2���� �迭�� ��´�.
	// x ��� y ���� �ε���
	const AnimationAsset& mAnimationAsset;
	unsigned int mAnimationIndex;
	unsigned int mFrameIndex;

	/// �ð� ����
	float mAnimationProgress;	// �ִϸ��̼� ��� �ð�

	// ��Ʈ�� ���� ��ġ
	D2D1_RECT_F mPositionInfo;

};

