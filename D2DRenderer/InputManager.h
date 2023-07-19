#pragma once

#include <Windows.h>
#include <vector>

struct MousePos
{
	float xPos;
	float yPos;
};

enum class KEY_STATE
{
	NONE,	// 눌리지 않았고, 이전에도 눌리지 않은 상태
	TAP,	// 막 누른 시점
	HOLD,	// 누르고 있는
	AWAY,	// 막 뗀 시점
};

class InputManager
{
public:
	InputManager();
	~InputManager() = default;

	void Init();
	void Update();

	inline KEY_STATE GetKeyState(WORD keyCode) const;
	inline const MousePos& GetMousePos() const;

	//임시
	HWND GetHwnd() { return _hWnd; }

private:
	enum { KEY_STATES_SIZE = 256 };

	//임시
	HWND _hWnd = 0;


	KEY_STATE mKeyStates[KEY_STATES_SIZE];
	MousePos mMousePos;
};

KEY_STATE InputManager::GetKeyState(WORD keyCode) const
{
	return mKeyStates[keyCode];
}

const MousePos& InputManager::GetMousePos() const
{
	return mMousePos;
}
