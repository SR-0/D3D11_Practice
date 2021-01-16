#include "Graphics.h"





// local includes
#include "Window.h"
#include "Shaders.h"





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





#pragma region CORE CREATE - CORE SETUP - CORE UPDATE - CORE RENDER - CORE DESTROY

void Graphics::create(Window* window)
{
	createGraphics(window);
	createShaders();
	createScene(window);
}

void Graphics::setup()
{
	setupGraphics();
	setupShaders();
	setupScene();
}

void Graphics::update()
{
	updateGraphics();
	updateShaders();
	updateScene();
}

void Graphics::render()
{
	clear();
	draw();
	display();
}

void Graphics::destroy()
{
	destroyGraphics();
	destroyShaders();
	destroyScene();
}

#pragma endregion CORE CREATE - CORE SETUP - CORE UPDATE - CORE RENDER - CORE DESTROY






#pragma region SPECIFIC CORE CREATION/INITIALIZATION

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

bool Graphics::createShaders()
{
	// vertext shader creation/initialization
	VertexShader1 = new HLSLShader;
	VertexShader1->createHLSLFile(L"resource/shaders/VS1.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &VS_Buffer, nullptr,

		"float4 VS(float4 inPos : POSITION) : SV_POSITION\n"
		"{\n"
		"	return inPos;\n"
		"};\n"

	);

	// pixel shader creation/initialization
	PixelShaderRed = new HLSLShader;
	PixelShaderRed->createHLSLFile(L"resource/shaders/PSRed.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &PS_Buffer, nullptr,

		"float4 PS() : SV_TARGET\n"
		"{\n"
		"	return float4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\n"

	);

	PixelShaderGreen = new HLSLShader;
	PixelShaderGreen->createHLSLFile(L"resource/shaders/PSGrean.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &PS_Buffer, nullptr,

		"float4 PS() : SV_TARGET\n"
		"{\n"
		"	return float4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\n"

	);

	PixelShaderBlue = new HLSLShader;
	PixelShaderBlue->createHLSLFile(L"resource/shaders/PSBlue.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &PS_Buffer, nullptr,

		"float4 PS() : SV_TARGET\n"
		"{\n"
		"	return float4(0.0f, 0.0f, 1.0f, 1.0f);\n"
		"}\n"

	);

	return true;
}

bool Graphics::createScene(class Window* window)
{
	createCompiledShaders();

	createAndAttachVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);

	createAndAttachPixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);

	Vertex3 vertex(
		Vertex(-0.5f, -0.5f),
		Vertex( 0.0f,  0.5f),
		Vertex( 0.5f, -0.5f));

	createVertexBuffer(vertex.vertices);

	createInputLayout();

	return true;
}

#pragma endregion SPECIFIC CORE CREATION/INITIALIZATION





#pragma region SPECIFIC CORE SETUP

void Graphics::setupGraphics()
{
	// coming soon 
}

void Graphics::setupShaders()
{
	// coming soon 
}

void Graphics::setupScene()
{
	// coming soon 
}

#pragma endregion SPECIFIC CORE SETUP





#pragma endregion SPECIFIC CORE UPDATE

void Graphics::updateGraphics()
{
	// coming soon 
}

void Graphics::updateShaders()
{
	// coming soon 
}

void Graphics::updateScene()
{
	updateBackgroundColor();
}

#pragma endregion SPECIFIC CORE UPDATE





#pragma region SPECIFIC CORE RENDER

void Graphics::clear()
{
	const float backgroundColor[4] = { color.r, color.g, color.b, color.a };
	d3d11DeviceContext->ClearRenderTargetView(renderTargetView, backgroundColor);
}

void Graphics::draw()
{
	drawTriangle();
}

void Graphics::display()
{
	swapChain->Present(0, 0);
}

#pragma endregion SPECIFIC CORE RENDER





#pragma region SPECIFIC CORE DESTROY

void Graphics::destroyGraphics()
{
	swapChain->Release();
	d3d11Device->Release();
	d3d11DeviceContext->Release();
	backBuffer->Release();
	renderTargetView->Release();
}

void Graphics::destroyShaders()
{
	// vertex shader destruction
	delete VertexShader1;

	// pixel shader destruction
	delete PixelShaderRed;
	delete PixelShaderBlue;
	delete PixelShaderGreen;
}

void Graphics::destroyScene()
{
	triangleVertBuffer->Release();
	VS->Release();
	PS->Release();
	VS_Buffer->Release();
	PS_Buffer->Release();
	vertLayout->Release();
}

#pragma endregion SPECIFIC CORE DESTROY





#pragma region SPECIFIC GRAPHICS CREATION/INITIALIZATION

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

#pragma endregion SPECIFIC GRAPHICS CREATION/INITIALIZATION





#pragma region SPECIFIC SHADER CREATION/INITIALIZATION

// possible

#pragma endregion SPECIFIC SHADER CREATION/INITIALIZATION





#pragma region SPECIFIC SCENE CREATION/INITIALIZATION

void Graphics::createCompiledShaders()
{
	VertexShader1->compile();
	PixelShaderBlue->compile();
}

void Graphics::createAndAttachVertexShader(
	const void*				pShaderByteCode, 
	SIZE_T					byteCodeLength, 
	ID3D11ClassLinkage*		pClassLinkage,
	ID3D11VertexShader**	ppVertexShader)
{
	hResult = d3d11Device->CreateVertexShader(pShaderByteCode, byteCodeLength, pClassLinkage, ppVertexShader);
	d3d11DeviceContext->VSSetShader(VS, 0, 0);
}

void Graphics::createAndAttachPixelShader(
	const void*				pShaderByteCode, 
	SIZE_T					byteCodeLength, 
	ID3D11ClassLinkage*		pClassLinkage,
	ID3D11PixelShader**		ppPixelShader)
{
	hResult = d3d11Device->CreatePixelShader(pShaderByteCode, byteCodeLength, pClassLinkage, ppPixelShader);
	d3d11DeviceContext->PSSetShader(PS, 0, 0);
}

void Graphics::createVertexBuffer(Vertex vertex[])
{
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
}

void Graphics::createInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA },
	};
	hResult = d3d11Device->CreateInputLayout(layout, 1, VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), &vertLayout);
}

#pragma endregion SPECIFIC SCENE CREATION/INITIALIZATION

void Graphics::updateBackgroundColor()
{
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
