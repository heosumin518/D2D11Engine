#pragma once

#include <d2d1.h>
#include <vector>
#include "FrameInfo.h"


class AnimationAsset
{
public:
	AnimationAsset(ID2D1Bitmap* _bitmap, const std::vector<std::vector<FrameInfo>>& _bitmapInfo, float _frameDistance);
	~AnimationAsset();
	/*
	// 복사생성자와 대입연산자 정의.

	AnimationAsset(const AnimationAsset& other)
		: AnimationAsset(other.bitmap, other.bitmapInfo, other.frameDistance)
	{
	}

	AnimationAsset& operator=(const AnimationAsset& other)
	{
		if (this == &other)
		{
			return *this;
		}
		bitmap = other.bitmap;
		bitmapInfo = other.bitmapInfo;
		frameDistance = other.frameDistance;

		bitmap->AddRef();
		return *this;
	}*/

	inline ID2D1Bitmap* GetBitmap() const;
	inline const std::vector<std::vector<FrameInfo>>& GetBitmapInfo() const;
	inline float GetFrameDistance() const;

private:
	ID2D1Bitmap* mBitmap;
	std::vector<std::vector<FrameInfo>> mFrameAnimationInfo;	// 각 행 마다 길이가 다를 수 있게 vector 두 개 씌웠다.

	/// 시간 정보
	float mFrameDistance;	// 프레임 간격 // 애니메이션 재생 속도

};

ID2D1Bitmap* AnimationAsset::GetBitmap() const
{
	return mBitmap;
}

const std::vector<std::vector<FrameInfo>>& AnimationAsset::GetBitmapInfo() const
{
	return mFrameAnimationInfo;
}

float AnimationAsset::GetFrameDistance() const
{
	return mFrameDistance;
}
