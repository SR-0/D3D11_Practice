#include "Graphics.h"

// local includes
#include "Window.h"



#pragma region CONSTRUCTORS - DESTRUCTORS

Graphics::Graphics(class Window* window)
	:
	color(Color(0.f, 0.f, 0.f, 1.f)),
	colorModifier(Color(1.f, 1.f, 1.f, 1.f))
{
	create(window);
	setup();
}

Graphics::~Graphics()
{
	destroy();
}

#pragma endregion CONSTRUCTORS - DESTRUCTORS



#pragma region CREATE - SETUP - DESTROY

void Graphics::create(Window* window)
{
	createGraphics(window);
	createScene(window);
}

void Graphics::setup()
{
	// none atm
}

void Graphics::destroy()
{
	destroyCOMObjects();
}

#pragma endregion CREATE - SETUP - DESTROY



#pragma region CORE INITIALIZATION/CREATION

bool Graphics::createGraphics(class Window* window)
{
	createBufferDescription(
		window->getWidth(),
		window->getHeight(),
		60,
		1,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
		DXGI_MODE_SCALING_UNSPECIFIED);

	createSwapChainDescription(
		bufferDescription,
		1,
		0,
		DXGI_USAGE_RENDER_TARGET_OUTPUT,
		1,
		window->getHandle(),
		TRUE,
		DXGI_SWAP_EFFECT_DISCARD);

	createDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&swapChainDescription,
		&swapChain,
		&d3d11Device,
		NULL,
		&d3d11DeviceContext);

	createBackBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	createRenderTargetView(backBuffer, NULL, &renderTargetView);

	return true;
}

bool Graphics::createScene(class Window* window)
{
	// compile shaders from shader file
	hResult = D3DCompileFromFile(L"resource/shaders/VSTest.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &VS_Buffer, nullptr);
	hResult = D3DCompileFromFile(L"resource/shaders/PSTest.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &PS_Buffer, nullptr);

	// create the shader objects
	hResult = d3d11Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
	hResult = d3d11Device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);

	// set vertex and pixel shaders
	d3d11DeviceContext->VSSetShader(VS, 0, 0);
	d3d11DeviceContext->PSSetShader(PS, 0, 0);

	// create vertex buffer
	Vertex vertex[] =
	{
		Vertex(-0.5f, -0.5f),
		Vertex( 0.0f,  0.5f),
		Vertex( 0.5f, -0.5f)
	};

	D3D11_BUFFER_DESC vertexBufferDescription;
	ZeroMemory(&vertexBufferDescription, sizeof(D3D11_BUFFER_DESC));

	vertexBufferDescription.Usage			= D3D11_USAGE_DEFAULT;
	vertexBufferDescription.ByteWidth		= sizeof(Vertex) * 3;
	vertexBufferDescription.BindFlags		= D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescription.CPUAccessFlags	= 0;
	vertexBufferDescription.MiscFlags		= 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	vertexBufferData.pSysMem = vertex;
	hResult = d3d11Device->CreateBuffer(&vertexBufferDescription, &vertexBufferData, &triangleVertBuffer);

	// create input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA },
	};
	hResult = d3d11Device->CreateInputLayout(layout, 1, VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), &vertLayout);

	return true;
}

#pragma endregion CORE INITIALIZATION/CREATION



#pragma region Graphics INITIALIZATION/CREATION

void Graphics::createBufferDescription(
	unsigned int				width,
	unsigned int				height,
	unsigned int				refreshRateNumerator,
	unsigned int				refreshRateDenominator,
	DXGI_FORMAT					format,
	DXGI_MODE_SCANLINE_ORDER	scanlineOrder,
	DXGI_MODE_SCALING			scaling)
{
	ZeroMemory(&bufferDescription, sizeof(DXGI_MODE_DESC));

	bufferDescription.Width						= width;
	bufferDescription.Height					= height;
	bufferDescription.RefreshRate.Numerator		= refreshRateNumerator;
	bufferDescription.RefreshRate.Denominator	= refreshRateDenominator;
	bufferDescription.Format					= format;
	bufferDescription.ScanlineOrdering			= scanlineOrder;
	bufferDescription.Scaling					= scaling;
}

void Graphics::createSwapChainDescription(
	DXGI_MODE_DESC		bufferDescription,
	unsigned int		sampleDescriptionCount,
	unsigned int		sampleDescriptionQuality,
	DXGI_USAGE			bufferUsage,
	unsigned int		bufferCount,
	HWND				outputWindow,
	BOOL				isWindowed,
	DXGI_SWAP_EFFECT	swapEffect)
{
	ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDescription.BufferDesc			= bufferDescription;
	swapChainDescription.SampleDesc.Count	= sampleDescriptionCount;
	swapChainDescription.SampleDesc.Quality	= sampleDescriptionQuality;
	swapChainDescription.BufferUsage		= bufferUsage;
	swapChainDescription.BufferCount		= bufferCount;
	swapChainDescription.OutputWindow       = outputWindow;
	swapChainDescription.Windowed			= isWindowed;
	swapChainDescription.SwapEffect			= swapEffect;
}

void Graphics::createDeviceAndSwapChain(
	IDXGIAdapter*			pAdapter,
	D3D_DRIVER_TYPE			driverType,
	HMODULE					software,
	UINT					flags,
	D3D_FEATURE_LEVEL*		pFeatureLevels,
	UINT					FeatureLevels,
	UINT					SDKVersion,
	DXGI_SWAP_CHAIN_DESC*	pSwapChainDescription,
	IDXGISwapChain**		ppSwapChain,
	ID3D11Device**			ppDevice,
	D3D_FEATURE_LEVEL*		pFeatureLevel,
	ID3D11DeviceContext**   ppImmediateContext)
{
	hResult = D3D11CreateDeviceAndSwapChain(
		pAdapter,
		driverType,
		software,
		flags,
		pFeatureLevels,
		FeatureLevels,
		SDKVersion,
		pSwapChainDescription,
		ppSwapChain,
		ppDevice,
		pFeatureLevel,
		ppImmediateContext
	);
}

void Graphics::createBackBuffer(UINT buffer, REFIID riid, void** ppSurface)
{
	hResult = swapChain->GetBuffer(buffer, riid, ppSurface);
}

void Graphics::createRenderTargetView(
	ID3D11Resource*					pResource,
	D3D11_RENDER_TARGET_VIEW_DESC*	pDescription,
	ID3D11RenderTargetView**		ppRenderTargetView)
{
	hResult = d3d11Device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	backBuffer->Release();
}

#pragma endregion Graphics INITIALIZATION/CREATION



#pragma region SCENE INITIALIZATION/CREATION

void Graphics::createInputLayout()
{
}

#pragma endregion SCENE INITIALIZATION/CREATION



void Graphics::destroyCOMObjects()
{
	swapChain->Release();
	d3d11Device->Release();
	d3d11DeviceContext->Release();
	renderTargetView->Release();
	triangleVertBuffer->Release();
	VS->Release();
	PS->Release();
	VS_Buffer->Release();
	PS_Buffer->Release();
	vertLayout->Release();
}

void Graphics::update()
{
	updateBackgroundColor();
}

void Graphics::render()
{
	clear();
	draw();
	display();
}

void Graphics::updateBackgroundColor()
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

void Graphics::clear()
{
	// clear backbuffer to updated color
	const FLOAT backgroundColor[4] = { color.r, color.g, color.b, color.a };
	d3d11DeviceContext->ClearRenderTargetView(renderTargetView, backgroundColor);
}

void Graphics::draw()
{
	// draw scene
	drawTriangle();
}

void Graphics::display()
{
	// present backbuffer to screen
	swapChain->Present(0, 0);
}

void Graphics::drawTriangle()
{
	// set vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	d3d11DeviceContext->IASetVertexBuffers(0, 1, &triangleVertBuffer, &stride, &offset);

	// set input layout
	d3d11DeviceContext->IASetInputLayout(vertLayout);

	// set primitive topology
	d3d11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// create viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX	= 0;
	viewport.TopLeftY	= 0;
	viewport.Width		= 800;
	viewport.Height		= 600;
	viewport.MaxDepth	= 1.f;

	// set viewport
	d3d11DeviceContext->RSSetViewports(1, &viewport);
	d3d11DeviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
	d3d11DeviceContext->VSSetShader(VS, nullptr, 0);
	d3d11DeviceContext->PSSetShader(PS, nullptr, 0);
	d3d11DeviceContext->Draw(3, 0); //3
}
