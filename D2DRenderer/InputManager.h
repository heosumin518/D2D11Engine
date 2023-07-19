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
	NONE,	// ������ �ʾҰ�, �������� ������ ���� ����
	TAP,	// �� ���� ����
	HOLD,	// ������ �ִ�
	AWAY,	// �� �� ����
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

	//�ӽ�
	HWND GetHwnd() { return _hWnd; }

private:
	enum { KEY_STATES_SIZE = 256 };

	//�ӽ�
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
