#pragma once

#include <d2d1.h>

class D2DRenderer;
namespace assignment4
{
	struct TransformInfo
	{
		float ScaleX;
		float ScaleY;
		float Rotation;
		float MoveX;
		float MoveY;
	};

	class GameObject
	{
	public:
		GameObject(const D2D1_RECT_F& rectangle, const TransformInfo& transformInfo);
		virtual ~GameObject() = default;

		virtual void Update();
		virtual void Render(D2DRenderer* d2dRenderer, D2D1::Matrix3x2F transform);

		inline D2D_RECT_F GetGameObjectWorldRect() const;
		inline const D2D1::Matrix3x2F& GetWorldTransform() const;

	protected:
		enum { RESERVE_SIZE = 512 };

		D2D1_RECT_F mRectangle;
		TransformInfo mTransformInfo;
		D2D1::Matrix3x2F mTransform;
	};

	D2D_RECT_F GameObject::GetGameObjectWorldRect() const
	{
		D2D1_POINT_2F TL = mTransform.TransformPoint(D2D1::Point2F(mRectangle.left, mRectangle.top));
		D2D1_POINT_2F BR = mTransform.TransformPoint(D2D1::Point2F(mRectangle.right, mRectangle.bottom));

		D2D_RECT_F result = { TL.x, TL.y, BR.x, BR.y };

		return result;
	}

	const D2D1::Matrix3x2F& GameObject::GetWorldTransform() const
	{
		return mTransform;
	}
}

