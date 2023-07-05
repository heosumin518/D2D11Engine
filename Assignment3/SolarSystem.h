#pragma once

#include <d2d1.h>
#include "GameProcessor.h"

class D2DRenderer;

namespace assignment3
{
	class GameObject;

	class SolarSystem : public gameProcessor::GameProcessor
	{
	public:
		SolarSystem(UINT width, UINT height, std::wstring name);
		virtual ~SolarSystem() = default;

		virtual bool Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Destroy() override;

	private:
		D2DRenderer* mD2dRenderer;

		GameObject* mSun;/*
		GameObject* mEarth;
		GameObject* mMoon;*/
	};
}

