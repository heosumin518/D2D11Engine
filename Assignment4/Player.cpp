#include "Player.h"

namespace assignment4
{
	Player::Player(const D2D1_RECT_F& rectangle, const TransformInfo& transformInfo)
		: GameObject(rectangle, transformInfo)
	{
	}

	void Player::HandleInput(InputManager* inputManager)
	{

		//if (inputManager->GetKeyState(VK_UP) == KEY_STATE::HOLD)
		//{
		//	OutputDebugString(L"���� �̵�\n");
		//	mTransformInfo.MoveY++;
		//}
		//else if (inputManager->GetKeyState(VK_DOWN) == KEY_STATE::HOLD)
		//{
		//	OutputDebugString(L"�Ʒ��� �̵�\n");
		//	mTransformInfo.MoveY--;
		//}
		//if (inputManager->GetKeyState(VK_LEFT) == KEY_STATE::HOLD)
		//{
		//	OutputDebugString(L"���� �̵�\n");
		//	mTransformInfo.MoveX--;
		//}
		//else if (inputManager->GetKeyState(VK_RIGHT) == KEY_STATE::HOLD)
		//{
		//	OutputDebugString(L"������ �̵�\n");
		//	mTransformInfo.MoveX++;
		//}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			OutputDebugString(L"���� �̵�\n");
			mTransformInfo.MoveY-=5;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			OutputDebugString(L"�Ʒ��� �̵�\n");
			mTransformInfo.MoveY+=5;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			OutputDebugString(L"���� �̵�\n");
			mTransformInfo.MoveX-=5;
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			OutputDebugString(L"������ �̵�\n");
			mTransformInfo.MoveX+=5;
		}
	}
}
