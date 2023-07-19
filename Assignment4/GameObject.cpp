#include "GameObject.h"
#include "D2DRenderer.h"

namespace assignment4
{
	GameObject::GameObject(const D2D1_RECT_F& rectangle, const TransformInfo& transformInfo)
		: mRectangle(rectangle)
		, mTransformInfo(transformInfo)
		, mTransform(D2D1::Matrix3x2F::Identity())
	{
	}

	void GameObject::Update()
	{
		//mTransform = D2D1::Matrix3x2F::Scale({ mTransformInfo.ScaleX, mTransformInfo.ScaleY })
		//	* D2D1::Matrix3x2F::Rotation(mTransformInfo.Rotation)
		//	* D2D1::Matrix3x2F::Translation(mTransformInfo.MoveX, mTransformInfo.MoveY);

		mTransform = D2D1::Matrix3x2F::Scale({ mTransformInfo.ScaleX, mTransformInfo.ScaleY })
			* D2D1::Matrix3x2F::Rotation(mTransformInfo.Rotation)
			* D2D1::Matrix3x2F::Translation(mTransformInfo.MoveX, mTransformInfo.MoveY);
	}

	void GameObject::Render(D2DRenderer* d2dRenderer, D2D1::Matrix3x2F transform)
	{
		d2dRenderer->DrawRectangle(mRectangle, mTransform * transform);
	}


}