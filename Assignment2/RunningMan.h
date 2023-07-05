#pragma once

#include <d2d1.h>
#include "GameProcessor.h"
#include "AnimationInstance.h"
#include "AnimationAsset.h"
#include <vector>
#include <map>
#include <d2d1helper.h>

class D2DRenderer;

namespace assignment2
{
	class RunningMan : public gameProcessor::GameProcessor
	{
	public:
		RunningMan(UINT width, UINT height, std::wstring name);
		virtual ~RunningMan() = default;

		std::vector<AnimationInstance> animationInstances;
		std::map<const WCHAR*, AnimationAsset*> animationAssets;

		virtual bool Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Destroy() override;

	private:
		D2DRenderer* mD2dRenderer;
		ID2D1Bitmap* playerBitmap;
		ID2D1Bitmap* backgroundBitmap;
	};
}


