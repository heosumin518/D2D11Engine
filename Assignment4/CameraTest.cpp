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
		//D2D1InvertMatrix(&viewPortTransform);	// ȭ�� ��ȯ�� ����
		//mPlayer->Render(mD2dRenderer, inverse * viewPortTransform);
		// �÷��̾� ����

		// ī�޶� ĸó�� ũ��� ���� ������ ����� �����
		// ������ ������Ʈ�� ������ �ϱ� ���� �� ����� ������� �������Ѵ�.

		D2D1::Matrix3x2F invertTransform = mCamera->GetCameraTransform();
		D2D1InvertMatrix(&invertTransform);

		/// 1. AABB�� �����Ѵ�.
		/// 2. ī�޶� ũ�⸦ ȭ�麸�� �۰��ؼ� �ٱ����� ������ �� �� ���̴� �� Ȯ���ϱ�
		///	a. ī�޶��� ���� rect�� �������ϱ�
		/// AABB ���϶� ������ �Ѵ�.
		/// �Ʒ� if ���� �����ؾ��� �Լ�.
		/// CheckCollisioonAABB �� ���� ������Ʈ�� ���巺Ʈ�� ī�޶� ������Ʈ�� ���巺Ʈ ���� ��ġ���� Ȯ���Ѵ�.

		if (CheckCollisionAABB(mPlayer->GetGameObjectWorldRect(), mCamera->GetCameraWorldRect()))	// �ӽ÷� ! ��.
		{
			mPlayer->Render(mD2dRenderer, mPlayer->GetWorldTransform() * invertTransform * mCamera->GetScreenTransform());
		}
		// ���������� �ƿ� �������� ���� �������� �ƴϸ� �ش� ������Ʈ rect �� ���� �ٲܰ������� 1, 2 ��� �ϼ� �� �����غ���

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
			OutputDebugString(L"�浹 �����ĤĤĤĤĤ�\n");
			result = false;
		}
		if (cameraRect.bottom > playerRect.bottom || cameraRect.top < playerRect.top)
		{
			OutputDebugString(L"�浹 �����ĤĤĤĤĤ�\n");
			result = false;
		}

		//D2D_POINT_2F m_Center = { 0 }; // �߾�
		//D2D_POINT_2F m_Extend = { 0 }; // x,y�� Ȯ�尪	
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
