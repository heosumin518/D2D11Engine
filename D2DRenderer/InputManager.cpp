#include "InputManager.h"
#include "WinApp.h"
#include <Windows.h>
#include <cassert>

InputManager::InputManager()
	: mKeyStates{ KEY_STATE::NONE, }
	, mMousePos{}
{
}

void InputManager::Init()
{
	memset(&mMousePos, 0, sizeof(mMousePos));
	memset(mKeyStates, static_cast<int>(KEY_STATE::NONE), KEY_STATES_SIZE * sizeof(KEY_STATE));
}

void InputManager::Update()
{
	POINT curMousePos;
	GetCursorPos(&curMousePos);

	if (ScreenToClient(GetHwnd(), &curMousePos) != false)
	{
		mMousePos = { static_cast<float>(curMousePos.x), static_cast<float>(curMousePos.y) };
	}

	for (int i = 0; i < KEY_STATES_SIZE; ++i)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			switch (mKeyStates[i])
			{
				case KEY_STATE::NONE:
				case KEY_STATE::AWAY:
					mKeyStates[i] = KEY_STATE::TAP;
					break;
				case KEY_STATE::TAP:
				case KEY_STATE::HOLD:
					mKeyStates[i] = KEY_STATE::HOLD;
					break;
				default:
					assert(false);
					break;
			}
		}
		else
		{
			switch (mKeyStates[i])
			{
				case KEY_STATE::NONE:
				case KEY_STATE::AWAY:
					mKeyStates[i] = KEY_STATE::NONE;
					break;
				case KEY_STATE::TAP:
				case KEY_STATE::HOLD:
					mKeyStates[i] = KEY_STATE::AWAY;
					break;
				default:
					assert(false);
					break;
			}
		}
	}
}