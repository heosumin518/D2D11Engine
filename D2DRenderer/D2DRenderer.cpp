// D2DRenderer.cpp : ���� ���̺귯���� ���� �Լ��� �����Ѵ�.
// D2DRenderer : D2D ���� �������̽�

#include "pch.h"
#include "framework.h"
#include "D2DRenderer.h"
#include "WinApp.h"

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")


D2DRenderer::~D2DRenderer()
{
	if (m_pIWICImagingFactory) m_pIWICImagingFactory->Release();
	if (m_pRenderTarget) m_pRenderTarget->Release();
	if (m_pD2DFactory) m_pD2DFactory->Release();

	// COM ��� ��
	CoUninitialize();
}


HRESULT D2DRenderer::Initialize()
{
	HRESULT hr = S_OK;

	// COM���
	hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		// ����Ÿ���� ������ִ����丮��ü�� �����ϰ� �������̽� �����͸����´�.
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	}
	if (SUCCEEDED(hr))
	{
		// ����Ÿ���� ������ִ����丮��ü�� �����ϰ� �������̽� �����͸����´�.
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
		if (FAILED(hr))
			return false;

		// �̹� �����찡������� ���¿��� ������ ����� ���Ѵ�.
		RECT rc;
		GetClientRect(gameProcessor::WinApp::GetHwnd(), &rc);
		D2D1_SIZE_U size = D2D1::SizeU(
			static_cast<UINT>(rc.right - rc.left),
			static_cast<UINT>(rc.bottom - rc.top)
		);

		// ���丮�� �������ڵ�,����� �Ѱ� ����Ÿ���� �����.
		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(gameProcessor::WinApp::GetHwnd(), size),
			&m_pRenderTarget
		);
	}

	if (FAILED(hr))
		return false;

	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush);

	}

	if (FAILED(hr))
		return false;

	// �ؽ�Ʈ
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pDWriteFactory->CreateTextFormat(
			L"Bernard MT Condensed",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			50.0f,
			L"", //locale
			&m_pDWriteTextFormat
		);
	}
	if (FAILED(hr))
		return false;

	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		m_pDWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_pDWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	if (SUCCEEDED(hr))
	{
		// WIC Factory �������̽� ���
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_pIWICImagingFactory)
		);
	}

	if (FAILED(hr))
	{
		_com_error err(hr);
		MessageBox(gameProcessor::WinApp::GetHwnd(), err.ErrorMessage(), L"FAILED", MB_OK);
	}

	return true;
}

void D2DRenderer::BeginDraw()
{
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear({1.f, 1.f, 1.f, 1.f});
}

void D2DRenderer::EndDraw()
{
	HRESULT hr = m_pRenderTarget->EndDraw();
	// ���н� ����Ÿ�� �缺�������� ���д� �׷��Ⱦƴ��� ����
}

HRESULT D2DRenderer::CreateD2DBitmapFromFile(const WCHAR* strFilePath, ID2D1Bitmap** pID2D1Bitmap)
{
	HRESULT hr;
	// Create a decoder
	IWICBitmapDecoder* pDecoder = NULL;

	hr = m_pIWICImagingFactory->CreateDecoderFromFilename(
		strFilePath,                      // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);


	// Retrieve the first frame of the image from the decoder
	IWICBitmapFrameDecode* pFrame = NULL;

	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	IWICFormatConverter* pConverter = NULL;

	//Step 3: Format convert the frame to 32bppPBGRA
	if (SUCCEEDED(hr))
	{
		hr = m_pIWICImagingFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pFrame,                          // Input bitmap to convert
			GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
			WICBitmapDitherTypeNone,         // Specified dither pattern
			NULL,                            // Specify a particular palette 
			0.f,                             // Alpha threshold
			WICBitmapPaletteTypeCustom       // Palette translation type
		);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, pID2D1Bitmap);
	}


	if (pFrame != NULL)
		pFrame->Release();

	if (pConverter != NULL)
		pConverter->Release();

	if (pDecoder != NULL)
		pDecoder->Release();

	if (FAILED(hr))
	{
		_com_error err(hr);
		::MessageBox(gameProcessor::WinApp::GetHwnd(), strFilePath, L"FAILED", MB_OK);
	}

	return hr;
}

void D2DRenderer::DrawRectangle(const D2D1_RECT_F& rect, const D2D1::Matrix3x2F matrix)
{
	m_pRenderTarget->SetTransform(matrix);
	m_pRenderTarget->DrawRectangle(&rect, m_pBrush);
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void D2DRenderer::DrawBitmap(ID2D1Bitmap* bitmap)
{
	m_pRenderTarget->DrawBitmap(bitmap);
}

void D2DRenderer::DrawAnimationBitmap(ID2D1Bitmap* bitmap, D2D1_RECT_F spriteRect, D2D1_RECT_F worldRect)
{
	m_pRenderTarget->DrawBitmap(bitmap, spriteRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, worldRect);
}
