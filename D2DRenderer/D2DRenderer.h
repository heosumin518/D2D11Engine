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

	// �����ϴ� ��Ʈ�� ����
	HRESULT			CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** pID2D1Bitmap);
	// ����� ��� ȣ���ϸ鼭 ī���Ͱ� 0�� �Ǹ� �������� ��Ͽ��� �����Ѵ�.
	void			ReleaseD2DBitmapFromFile(ID2D1Bitmap* pID2D1Bitmap);

private:
	ID2D1SolidColorBrush*	m_pBrush				= nullptr;		// ����Ÿ�ٿ��������� �귯���� �������̽� ������
	ID2D1Factory*			m_pD2DFactory			= nullptr;		// D2D ��ü �������̽� ������ ����	// Direct2D�� ����ϱ� ���� ��ü���� �����
	IDWriteFactory*			m_pDWriteFactory		= nullptr;		// TextFormat������ ���� ���丮
	IDWriteTextFormat*		m_pDWriteTextFormat		= nullptr;		// �⺻ �ؽ�Ʈ ����� ���� Format
	IWICImagingFactory*		m_pIWICImagingFactory	= nullptr;		// WIC �������̽�	// D2D��Ʈ�� ������ ���� �̹��� ó�� �������̽�
	ID2D1HwndRenderTarget*	m_pRenderTarget			= nullptr;		// �� �����쿡 �����ϱ� ���� ����Ÿ�� Ÿ��.

	//���ڿ��� ��Ʈ������ �̷���� �ֵ��� �����ϴ� ����Ʈ
	std::list <std::pair<std::wstring, ID2D1Bitmap*>> m_SharingD2DBitmaps;

};

