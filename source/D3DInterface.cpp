#include "D3DInterface.h"

#include "Window.h"

D3DInterface::D3DInterface(class Window* window)
	:
	color(Color(0.f, 0.f, 0.f, 1.f)),
	colorModifier(Color(1.f, 1.f, 1.f, 1.f))
{
	initializeD3DApp(window);
	initializeScene();

	// make this better.... SR_0
	layout = new D3D11_INPUT_ELEMENT_DESC[]
	{ 
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA }, 
	};
}

D3DInterface::~D3DInterface()
{
	releaseObjects();
	
	// make this better.... SR_0
	delete layout;
}

DXGI_MODE_DESC D3DInterface::createBufferDescription(
	unsigned int				width,
	unsigned int				height,
	unsigned int				refreshRateNumerator,
	unsigned int				refreshRateDenominator,
	DXGI_FORMAT					DXGIFormat,
	DXGI_MODE_SCANLINE_ORDER 	DXGIMScanlineOrder,
	DXGI_MODE_SCALING			DXGIMScaling)
{
	// describe buffer
	DXGI_MODE_DESC bufferDescription;

	ZeroMemory(&bufferDescription, sizeof(DXGI_MODE_DESC));

	bufferDescription.Width						= width;
	bufferDescription.Height					= height;
	bufferDescription.RefreshRate.Numerator		= refreshRateNumerator;
	bufferDescription.RefreshRate.Denominator	= refreshRateDenominator;
	bufferDescription.Format					= DXGIFormat;
	bufferDescription.ScanlineOrdering			= DXGIMScanlineOrder;
	bufferDescription.Scaling					= DXGIMScaling;

	return bufferDescription;
}

DXGI_SWAP_CHAIN_DESC D3DInterface::createSwapChainDescription(
	DXGI_MODE_DESC&		bufferDescription,
	unsigned int		sampleDescriptionCount,
	unsigned int		sampleDescriptionQuality,
	DXGI_USAGE			DXGIUsage,
	unsigned int		bufferCount,
	HWND				hWnd,
	BOOL				isWindowed,
	DXGI_SWAP_EFFECT	DXGISwapEffect)
{
	// describe SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDescription;

	ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDescription.BufferDesc			= bufferDescription;
	swapChainDescription.SampleDesc.Count	= sampleDescriptionCount;
	swapChainDescription.SampleDesc.Quality	= sampleDescriptionQuality;
	swapChainDescription.BufferUsage		= DXGIUsage;
	swapChainDescription.BufferCount		= bufferCount;
	swapChainDescription.OutputWindow       = hWnd;
	swapChainDescription.Windowed			= isWindowed;
	swapChainDescription.SwapEffect			= DXGISwapEffect;

	return swapChainDescription;
}

bool D3DInterface::initializeD3DApp(class Window* window)
{
	HRESULT hResult;

	// describe buffer
	DXGI_MODE_DESC bufferDescription = createBufferDescription(
		window->getWidth(),
		window->getHeight(),
		60,
		1,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
		DXGI_MODE_SCALING_UNSPECIFIED
	);

	// describe SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDescription = createSwapChainDescription(
		bufferDescription,
		1,
		0,
		DXGI_USAGE_RENDER_TARGET_OUTPUT,
		1,
		window->getHandle(),
		TRUE,
		DXGI_SWAP_EFFECT_DISCARD
	);

	// create swapChain
	hResult = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&swapChainDescription,
		&swapChain,
		&d3d11Device,
		NULL,
		&d3d11DeviceContext
	);

	// create backBuffer
	ID3D11Texture2D* backBuffer;
	hResult = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	// create render target
	hResult = d3d11Device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	backBuffer->Release();

	// set render target
	d3d11DeviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

	return true;
}

void D3DInterface::releaseObjects()
{
	// release COM objects
	swapChain->Release();
	d3d11Device->Release();
	d3d11DeviceContext->Release();
}

bool D3DInterface::initializeScene()
{

	return true;
}

void D3DInterface::updateScene()
{
	// update silly colors
	color.r += colorModifier.r * 0.00005f;
	color.g += colorModifier.g * 0.00002f;
	color.b += colorModifier.b * 0.00001f;

	if (color.r >= 1.f || color.r <= 0.f)
	{
		colorModifier.r *= -1;
	}

	if (color.g >= 1.f || color.g <= 0.f)
	{
		colorModifier.g *= -1;
	}

	if (color.b >= 1.f || color.b <= 0.f)
	{
		colorModifier.b *= -1;
	}
}

void D3DInterface::drawScene()
{
	// clear backbuffer to updated color
	const FLOAT backgroundColor[4] = { color.r, color.g, color.b, color.a };
	d3d11DeviceContext->ClearRenderTargetView(renderTargetView, backgroundColor);

	// present backbuffer to screen
	swapChain->Present(0, 0);
}
