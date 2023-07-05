#pragma once

#include <vector>
#include <d2d1.h>
//#include "D2DRenderer.h"

class D2DRenderer;
namespace assignment3
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
		~GameObject();

		void Update();
		void Render(D2DRenderer* d2dRenderer);

		inline void SetParentGameObject(GameObject* parentGameObject);
		inline void AddChildGameObject(GameObject* childGameObject);

	private:
		enum { RESERVE_SIZE = 512 };

		D2D1_RECT_F mRectangle;
		TransformInfo mTransformInfo;
		D2D1::Matrix3x2F mTransform;

		GameObject* mParentGameObject;
		std::vector<GameObject*> mChildGameObjects;
	};

	void GameObject::SetParentGameObject(GameObject* parentGameObject)
	{
		mParentGameObject = parentGameObject;
	}
	void GameObject::AddChildGameObject(GameObject* childGameObject)
	{
		mChildGameObjects.push_back(childGameObject);
	}
}