#pragma once

#include <string>
#include <list>
#include <dwrite.h>
#include <wincodec.h>

class D2DRenderer
{
public:
	D2DRenderer() = default;
	~D2DRenderer();

	HRESULT Initialize();
	void	BeginDraw();
	void	EndDraw();
	void	DrawRectangle(const D2D1_RECT_F& rect, const D2D1::Matrix3x2F matrix);

	// 공유하는 비트맵 생성
	HRESULT			CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** pID2D1Bitmap);
	// 릴리즈를 대신 호출하면서 카운터가 0이 되면 공유중인 목록에서 제거한다.
	void			ReleaseD2DBitmapFromFile(ID2D1Bitmap* pID2D1Bitmap);

private:
	ID2D1SolidColorBrush*	m_pBrush				= nullptr;		// 렌더타겟에서생성한 브러시의 인터페이스 포인터
	ID2D1Factory*			m_pD2DFactory			= nullptr;		// D2D 개체 인터페이스 포인터 변수	// Direct2D를 사용하기 위한 개체들을 만든다
	IDWriteFactory*			m_pDWriteFactory		= nullptr;		// TextFormat생성을 위한 팩토리
	IDWriteTextFormat*		m_pDWriteTextFormat		= nullptr;		// 기본 텍스트 출력을 위한 Format
	IWICImagingFactory*		m_pIWICImagingFactory	= nullptr;		// WIC 인터페이스	// D2D비트맵 생성을 위한 이미지 처리 인터페이스
	ID2D1HwndRenderTarget*	m_pRenderTarget			= nullptr;		// 한 윈도우에 렌더하기 위한 렌더타겟 타입.

	//문자열과 비트맵으로 이루어진 쌍들을 저장하는 리스트
	std::list <std::pair<std::wstring, ID2D1Bitmap*>> m_SharingD2DBitmaps;

};

