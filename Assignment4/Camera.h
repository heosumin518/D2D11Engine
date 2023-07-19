#pragma once


#include "InputManager.h"
#include <d2d1.h>

class D2DRenderer;

namespace assignment4
{
	class GameObject;

	class Camera
	{
	public:
		Camera(float speed, float width, float height, GameObject* ownerObjectOrNull = nullptr);
		~Camera() = default;

		void Update(float deltaTime, InputManager* inputManager);	// ī�޶� �̵��� ó��, �̵��� �ð� ��� ������Ʈ
		void Render(D2DRenderer* d2dRenderer, D2D1::Matrix3x2F transform);

		inline void CameraTranslate(float x, float y);	// Update ���� ī�޶� �̵��� ���� �Լ�
		inline const D2D1::Matrix3x2F& GetCameraTransform() const;
		inline const D2D1::Matrix3x2F& GetScreenTransform() const;
		inline D2D_RECT_F GetCameraWorldRect() const;
		inline D2D_VECTOR_2F GetCameraRectCenter();	// ī�޶��� �߽��� ��ġ ���ϱ�
		inline D2D_VECTOR_2F GetCameraXY();	// ī�޶� x, y ��ǥ ���ϱ�
		inline void SetOwnerObject(GameObject* ownerObjectOrNull);	// ī�޶� ������ ������Ʈ�� �����Ѵ�.

	private:
		D2D_RECT_F mCameraRect;
		D2D1::Matrix3x2F mCameraTransform;	// ���� ���������� ��ǥ�� �� �������� �ٲ��ִ� ��ȯ
		D2D1::Matrix3x2F mScreenTransform;	// �� ������ ���Ե� ��ǥ���� ��ũ�� ������ ��ǥ�� �ٲ��ִ� ��ȯ

		D2D_VECTOR_2F mCameraXY;	// ī�޶��� x, y ��ǥ
		float mScale;
		float mSpeed;

		int mCullCount = 0;	// ī�޶� �ȿ� �����ִ� ������Ʈ�� ��

		GameObject* mOwnerObjectOrNull;	// ī�޶� ������ ������Ʈ
	};

	const D2D1::Matrix3x2F& Camera::GetCameraTransform() const
	{
		return mCameraTransform;
	}

	const D2D1::Matrix3x2F& Camera::GetScreenTransform() const
	{
		return mScreenTransform;
	}

	D2D_RECT_F Camera::GetCameraWorldRect() const
	{
		D2D1_POINT_2F TL = mCameraTransform.TransformPoint(D2D1::Point2F(mCameraRect.left, mCameraRect.top));
		D2D1_POINT_2F BR = mCameraTransform.TransformPoint(D2D1::Point2F(mCameraRect.right, mCameraRect.bottom));

		D2D_RECT_F result = { TL.x, TL.y, BR.x, BR.y };

		return result;
	}

	void Camera::CameraTranslate(float x, float y)
	{
		mCameraXY.x += x;
		mCameraXY.y += y;
	}

	D2D_VECTOR_2F Camera::GetCameraRectCenter()
	{
		D2D_VECTOR_2F center = { mCameraRect.right * 0.5f, mCameraRect.bottom * 0.5f };
		return center;
	}

	D2D_VECTOR_2F Camera::GetCameraXY()
	{
		return mCameraXY;
	}

	void Camera::SetOwnerObject(GameObject* ownerObjectOrNull)
	{
		mOwnerObjectOrNull = ownerObjectOrNull;
	}
}
