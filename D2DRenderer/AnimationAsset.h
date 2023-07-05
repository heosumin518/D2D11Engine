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
	// ��������ڿ� ���Կ����� ����.

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
	std::vector<std::vector<FrameInfo>> mFrameAnimationInfo;	// �� �� ���� ���̰� �ٸ� �� �ְ� vector �� �� ������.

	/// �ð� ����
	float mFrameDistance;	// ������ ���� // �ִϸ��̼� ��� �ӵ�

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
