#pragma once

#include <d2d1.h>
#include "GameProcessor.h"
#include "TimeManager.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Camera.h"

class D2DRenderer;

namespace assignment4
{
	class CameraTest : public gameProcessor::GameProcessor
	{
	public:
		CameraTest(UINT width, UINT height, std::wstring name);
		virtual ~CameraTest() = default;

		virtual bool Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Destroy() override;

		bool CheckCollisionAABB(D2D_RECT_F playerRect, D2D_RECT_F cameraRect);

	private:
		D2DRenderer* mD2dRenderer;
		InputManager mInputManager;
		TimeManager mTimeManager;

		Player* mPlayer;
		Camera* mCamera;
		Camera* mMiniMapCamera;
	};
}

