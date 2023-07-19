#include "Camera.h"
#include "GameObject.h"
#include "D2DRenderer.h"

namespace assignment4
{
	// 좌표계 y축 반전시킨 뒤 화면 정중앙에 위치시킨다.
	Camera::Camera(float speed, float width, float height, GameObject* ownerObjectOrNull)
		: mCameraRect{-width/2, height / 2, width/2, -height/2}
		, mCameraTransform(D2D1::Matrix3x2F::Identity())
		, mScreenTransform(D2D1::Matrix3x2F::Scale(0.5f, -0.5f)*D2D1::Matrix3x2F::Translation(width * 0.5f, height * 0.5f))
		, mScale(1.f)
		, mSpeed(speed)
		, mOwnerObjectOrNull(ownerObjectOrNull)
	{
		mCameraXY = { 0.f, 0.f };

		//mCameraRect.left = 0.f;
		//mCameraRect.top = 0.f;
		//mCameraRect.right = 1280.f;
		//mCameraRect.bottom = 720.f;
	}

	void Camera::Update(float deltaTime, InputManager* inputManager)
	{
		// 추적하는 오브젝트가 있다 -> 카메라 위치 = 추적 오브젝트 위치
		if (mOwnerObjectOrNull != nullptr)
		{
			const D2D_VECTOR_2F cameraCenter = GetCameraRectCenter();
			//const D2D_VECTOR_2F ownerCenter = mOwnerObjectOrNull->GetWorldRectangle().GetCenter();


		}
		// 추적하는 오브젝트가 없다 -> 키보드 조작으로 카메라 움직이기
		else
		{
			/// TO DO : InputManager 쓰는걸로 수정
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				OutputDebugString(L"위로 이동\n");
				CameraTranslate(0.0f, +mSpeed * deltaTime);
			}
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				OutputDebugString(L"아래로 이동\n");
				CameraTranslate(0.0f, -mSpeed * deltaTime);
			}
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				OutputDebugString(L"왼쪽 이동\n");
				CameraTranslate(-mSpeed * deltaTime, 0.0f);
			}
			else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				OutputDebugString(L"오른쪽 이동\n");
				CameraTranslate(+mSpeed * deltaTime, 0.0f);
			}
		}

		mCameraTransform = D2D1::Matrix3x2F::Scale({ mScale, mScale })
			* D2D1::Matrix3x2F::Rotation((0.f))
			* D2D1::Matrix3x2F::Translation(mCameraXY.x, mCameraXY.y);

		D2D1::Matrix3x2F invertTransform = mCameraTransform;
		//D2D1::Matrix3x2F invertTransform = D2D1::Matrix3x2F::Translation(mCameraXY.x, mCameraXY.y);
		D2D1InvertMatrix(&invertTransform);	// 화면 변환을 적용
		//invertTransform.Invert(); 내장된 함수를 써서 반전해도 된다.
	}

	void Camera::Render(D2DRenderer* d2dRenderer, D2D1::Matrix3x2F transform)
	{
		d2dRenderer->DrawRectangle(mCameraRect, D2D1::Matrix3x2F::Identity() * transform);
	}

}