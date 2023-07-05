#pragma once

#include <d2d1.h>
#include "GameProcessor.h"

class D2DRenderer;

namespace assignment2
{
	class RunningMan : public gameProcessor::GameProcessor
	{
	public:
		RunningMan(UINT width, UINT height, std::wstring name);
		virtual ~RunningMan() = default;

		virtual bool Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Destroy() override;

	private:
		D2DRenderer* mD2dRenderer;
	};
}


