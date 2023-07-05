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
	/// 비트맵
	// 좌표정보 -> 2차원 배열에 담는다.
	// x 축과 y 축의 인덱스
	const AnimationAsset& mAnimationAsset;
	unsigned int mAnimationIndex;
	unsigned int mFrameIndex;

	/// 시간 정보
	float mAnimationProgress;	// 애니메이션 경과 시간

	// 비트맵 생성 위치
	D2D1_RECT_F mPositionInfo;

};

