// DemoApp.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DemoApp.h"

#include <d2d1.h>
#include <memory>

// D2DEngine프로젝트에서 기본 윈도우 생성,루프 기능 클래스로 래핑한 를 구현

DemoApp::DemoApp(HINSTANCE hInstance)
// GameApp클래스는 기본생성자가 없기때문에 자식클래스 DemoApp이 GameApp을 어떻게 생성자 호출할지 알려줘야한다.
	:GameApp::GameApp(hInstance)
{
	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());

	// 윈도우 클래스 준비하는 작업을 다른 함수로 만들고 싶지 않아 생성자에서 한다.
	// 실행파일에 합쳐진 데이터 영역에서 DemoApp에 관한 아이콘이나 문자를 가져와 윈도우 클래스 정보를 준비한다.

	// DemoApp에서 리소스를 얻어와 클래스 설정하기
	LoadStringW(m_hInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
	LoadStringW(m_hInstance, IDC_DEMOAPP, m_szWindowClass, MAX_LOADSTRING);

	m_wcex.hInstance = m_hInstance;
	m_wcex.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_DEMOAPP));
	m_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_wcex.hIconSm = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_SMALL));
	m_hAccelTable = LoadAccelerators(m_hInstance, MAKEINTRESOURCE(IDC_DEMOAPP));
}

// DemoApp의 파괴자 -> 멤버변수로 사용한 클래스의 파괴자 -> GameApp의 파괴자  순으로 호출된다.
DemoApp::~DemoApp()
{
	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());
}

bool DemoApp::Initialize()
{
	bool bRet = GameApp::Initialize();
	if (!bRet)
		return false;

	//HRESULT hr;

	//if (FAILED(hr))
	//{
	//	MessageBoxComError(hr);
	//	return false;
	//}
	return true;

}

void DemoApp::Render()
{
	D2DRenderer::m_pRenderTarget->BeginDraw();
	D2DRenderer::m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));

	//ID2D1SolidColorBrush* m_pLightSlateGrayBrush;

	//D2DRenderer::m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray), &m_pLightSlateGrayBrush);

	D2D1_RECT_F rect = D2D1::RectF(
		0.0f,
		0.f,
		50.f,
		50.f
	);

	D2D1::Matrix3x2F::Rotation(
		45.0f,
		D2D1::Point2F(468.0f, 331.5f));

	//D2DRenderer::m_pRenderTarget->DrawRectangle(&rect, m_pLightSlateGrayBrush);

	D2DRenderer::m_pRenderTarget->EndDraw();
}

void DemoApp::Update()
{
	GameApp::Update();

}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	DemoApp App(hInstance);
	App.Initialize();
	App.Loop();

	return (int)1;
}