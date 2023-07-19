#pragma once

#include "GameObject.h"
#include "InputManager.h"

namespace assignment4
{
	class Player : public GameObject
	{
	public:
		Player(const D2D1_RECT_F& rectangle, const TransformInfo& transformInfo);
		virtual ~Player() = default;

		virtual void HandleInput(InputManager* inputManager);
	};
}

