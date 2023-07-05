#pragma once

#include <d2d1.h>
#include "GameProcessor.h"

class D2DRenderer;

namespace assignment1
{

	class DemoApp : public gameProcessor::GameProcessor
	{
	public:
		DemoApp(UINT width, UINT height, std::wstring name);
		virtual ~DemoApp() = default;

		virtual bool Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Destroy() override;

	private:
		D2DRenderer* mD2dRenderer;

	};
}

