#include "GameObject.h"
#include "D2DRenderer.h"

namespace assignment3
{
	GameObject::GameObject(const D2D1_RECT_F& rectangle, const TransformInfo& transformInfo)
		: mRectangle(rectangle)
		, mTransformInfo(transformInfo)
		, mTransform(D2D1::Matrix3x2F::Identity())
		, mParentGameObject(nullptr)
	{
		mChildGameObjects.reserve(RESERVE_SIZE);
	}

	GameObject::~GameObject()
	{
		for (GameObject* child : mChildGameObjects)
		{
			delete child;
		}
		mChildGameObjects.clear();
	}

	void GameObject::Update()
	{
		mTransformInfo.Rotation += 0.1f;

		mTransform = D2D1::Matrix3x2F::Scale({ mTransformInfo.ScaleX, mTransformInfo.ScaleY })
			* D2D1::Matrix3x2F::Rotation(mTransformInfo.Rotation)
			* D2D1::Matrix3x2F::Translation(mTransformInfo.MoveX, mTransformInfo.MoveY);

		if (mParentGameObject != nullptr)
		{
			mTransform = mTransform * mParentGameObject->mTransform;
		}
		for (GameObject* child : mChildGameObjects)
		{
			child->Update();
		}
	}

	void GameObject::Render(D2DRenderer* d2dRenderer)
	{
		// 랜더러를 받아서 drawRect() 호출한다.
		d2dRenderer->DrawRectangle(mRectangle, mTransform);

		for (GameObject* child : mChildGameObjects)
		{
			child->Render(d2dRenderer);
		}
	}

}