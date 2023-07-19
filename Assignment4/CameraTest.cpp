#include <cassert>

#include "CameraTest.h"
#include "D2DRenderer.h"

namespace assignment4
{
	CameraTest::CameraTest(UINT width, UINT height, std::wstring name)
		: gameProcessor::GameProcessor(width, height, name)
		, mD2dRenderer(nullptr)
		, mPlayer(nullptr)
	{
	}


	bool CameraTest::Init()
	{
		mD2dRenderer = new D2DRenderer;
		mD2dRenderer->Initialize();

		mCamera = new Camera(500, mWidth, mHeight);

		TransformInfo transformInfo;
		transformInfo.ScaleX = 1.f;
		transformInfo.ScaleY = 1.f;
		transformInfo.Rotation = 0.f;
		transformInfo.MoveX = 0.f;
		transformInfo.MoveY = 0.f;
		/*transformInfo.MoveX = mCamera->GetCameraRectCenter().x;
		transformInfo.MoveY = mCamera->GetCameraRectCenter().y;*/

		mPlayer = new Player({ -100, -100, 100, 100 }, transformInfo);

		return true;
	}

	void CameraTest::Update()
	{
		//mPlayer->HandleInput(&mInputManager);
		const float DELTA_TIME = mTimeManager.GetDeltaTime();
		assert(DELTA_TIME >= 0.f);

		mTimeManager.Update();
		mPlayer->Update();
		mCamera->Update(DELTA_TIME, &mInputManager);
	}

	void CameraTest::Render()
	{
		mD2dRenderer->BeginDraw();



		/*D2D1::Matrix3x2F inverse = mCamera->GetCameraTransform();
		inverse = inverse * mCamera->GetScreenTransform();*/
		//D2D1::Matrix3x2F viewPortTransform = D2D1::Matrix3x2F::Translation(mCamera->GetCameraXY().x, mCamera->GetCameraXY().y);
		//D2D1InvertMatrix(&viewPortTransform);	// 화면 변환을 적용
		//mPlayer->Render(mD2dRenderer, inverse * viewPortTransform);
		// 플레이어 랜더

		// 카메라에 캡처된 크기와 축이 반전된 행렬을 만들어
		// 실제로 오브젝트를 렌더링 하기 전에 이 행렬을 적용시켜 렌더링한다.

		D2D1::Matrix3x2F invertTransform = mCamera->GetCameraTransform();
		D2D1InvertMatrix(&invertTransform);

		/// 1. AABB로 구현한다.
		/// 2. 카메라 크기를 화면보다 작게해서 바깥으로 나갔을 때 안 보이는 지 확인하기
		///	a. 카메라의 월드 rect도 렌더링하기
		/// AABB 참일때 렌더링 한다.
		/// 아래 if 문이 구현해야할 함수.
		/// CheckCollisioonAABB 는 게임 오브젝트의 월드렉트와 카메라 오브젝트의 월드렉트 끼리 겹치는지 확인한다.

		if (CheckCollisionAABB(mPlayer->GetGameObjectWorldRect(), mCamera->GetCameraWorldRect()))	// 임시로 ! 함.
		{
			mPlayer->Render(mD2dRenderer, mPlayer->GetWorldTransform() * invertTransform * mCamera->GetScreenTransform());
		}
		// 렌더했을때 아예 렌더링을 하지 않을건지 아니면 해당 오브젝트 rect 의 색상만 바꿀것인지는 1, 2 기능 완성 후 구현해보기

		mCamera->Render(mD2dRenderer, mCamera->GetScreenTransform());

		mD2dRenderer->EndDraw();
	}

	void CameraTest::Destroy()
	{
		delete mD2dRenderer;
		delete mPlayer;
	}

	bool CameraTest::CheckCollisionAABB(D2D_RECT_F playerRect, D2D_RECT_F cameraRect)
	{
		bool result = true;

		if (cameraRect.right < playerRect.left || cameraRect.left > playerRect.right)
		{
			OutputDebugString(L"충돌 해제ㅔㅔㅔㅔㅔㅔ\n");
			result = false;
		}
		if (cameraRect.bottom > playerRect.bottom || cameraRect.top < playerRect.top)
		{
			OutputDebugString(L"충돌 해제ㅔㅔㅔㅔㅔㅔ\n");
			result = false;
		}

		//D2D_POINT_2F m_Center = { 0 }; // 중앙
		//D2D_POINT_2F m_Extend = { 0 }; // x,y축 확장값	
		//// self min,max
		//float minBox1X = playerRect.right * 0.5f - playerRect.right;
		//float maxBox1X = playerRect.right * 0.5f + playerRect.right;
		//float minBox1Y = playerRect.bottom * 0.5f - playerRect.bottom;
		//float maxBox1Y = playerRect.bottom * 0.5f + playerRect.bottom;
		//// other min,max
		//float minBox2X = cameraRect.right * 0.5f - cameraRect.right;
		//float maxBox2X = cameraRect.right * 0.5f + cameraRect.right;
		//float minBox2Y = cameraRect.bottom * 0.5f - cameraRect.bottom;
		//float maxBox2Y = cameraRect.bottom * 0.5f + cameraRect.bottom;
		//// Check for no overlap conditions
		//if (maxBox1X < minBox2X || minBox1X > maxBox2X || maxBox1Y < minBox2Y || minBox1Y > maxBox2Y) {
		//	result = false;
		//}

		/*D2D_POINT_2F AminAABB = {};
		D2D_POINT_2F AmaxAABB = {};

		D2D_POINT_2F BminAABB = {};
		D2D_POINT_2F BmaxAABB = {};

		AminAABB.x = playerRect.right * 0.5f - playerRect.right;
		AmaxAABB.x = playerRect.right * 0.5f + playerRect.right;
		AminAABB.y = playerRect.bottom * 0.5f - playerRect.bottom;
		AmaxAABB.y = playerRect.bottom * 0.5f + playerRect.bottom;

		AminAABB.x = cameraRect.right * 0.5f - cameraRect.right;
		AmaxAABB.x = cameraRect.right * 0.5f + cameraRect.right;
		AminAABB.y = cameraRect.bottom * 0.5f - cameraRect.bottom;
		AmaxAABB.y = cameraRect.bottom * 0.5f + cameraRect.bottom;

		result = AminAABB.x <= BmaxAABB.x && AmaxAABB.x >= BminAABB.x &&
			AminAABB.y <= BmaxAABB.y && AmaxAABB.y >= BminAABB.y;*/

		return result;
	}

}
