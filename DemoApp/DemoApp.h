#pragma once

#include "resource.h"
#include "../D2DRenderer/GameApp.h"
#include "GameObject.h"

// DemoApp : 실제 프로젝트, GameApp을 상속받아 구조를 차용
class DemoApp : //public GameApp
{
public:
	DemoApp(HINSTANCE hInstance);
	virtual ~DemoApp();

	// override는 부모의 가상함수를 재정의 한다고 명확히 명시하여 새로 가상함수를 만드는 실수를 방지한다. 
	virtual bool Initialize() override;
	virtual void Render() override;
	virtual void Update() override;

private:
	
};