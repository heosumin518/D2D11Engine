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

		void Update(float deltaTime, InputManager* inputManager);	// 카메라 이동을 처리, 이동을 시간 기반 업데이트
		void Render(D2DRenderer* d2dRenderer, D2D1::Matrix3x2F transform);

		inline void CameraTranslate(float x, float y);	// Update 에서 카메라 이동시 사용될 함수
		inline const D2D1::Matrix3x2F& GetCameraTransform() const;
		inline const D2D1::Matrix3x2F& GetScreenTransform() const;
		inline D2D_RECT_F GetCameraWorldRect() const;
		inline D2D_VECTOR_2F GetCameraRectCenter();	// 카메라의 중심점 위치 구하기
		inline D2D_VECTOR_2F GetCameraXY();	// 카메라 x, y 좌표 구하기
		inline void SetOwnerObject(GameObject* ownerObjectOrNull);	// 카메라가 추적할 오브젝트를 설정한다.

	private:
		D2D_RECT_F mCameraRect;
		D2D1::Matrix3x2F mCameraTransform;	// 월드 공간에서의 좌표를 뷰 공간으로 바꿔주는 변환
		D2D1::Matrix3x2F mScreenTransform;	// 뷰 공간에 포함된 좌표들을 스크린 공간의 좌표로 바꿔주는 변환

		D2D_VECTOR_2F mCameraXY;	// 카메라의 x, y 좌표
		float mScale;
		float mSpeed;

		int mCullCount = 0;	// 카메라 안에 들어와있는 오브젝트의 수

		GameObject* mOwnerObjectOrNull;	// 카메라가 추적할 오브젝트
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
