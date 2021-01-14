#include "D3DInterface.h"

// local includes
#include "Window.h"

D3DInterface::D3DInterface(class Window* window)
	:
	color(Color(0.f, 0.f, 0.f, 1.f)),
	colorModifier(Color(1.f, 1.f, 1.f, 1.f))
{
	initialize(window);
}

D3DInterface::~D3DInterface()
{
	destruct();
}

void D3DInterface::initialize(Window* window)
{
	initializeD3D(window);
	initializeScene(window);
}

void D3DInterface::setup()
{
	// none atm
}

void D3DInterface::destruct()
{
	releaseObjects();

	// make this better.... SR_0
	delete layout;
}

bool D3DInterface::initializeD3D(class Window* window)
{
	HRESULT hResult;

	// describe buffer
	DXGI_MODE_DESC bufferDescription;
	ZeroMemory(&bufferDescription, sizeof(DXGI_MODE_DESC));

	bufferDescription.Width						= window->getWidth();
	bufferDescription.Height					= window->getHeight();
	bufferDescription.RefreshRate.Numerator		= 60;
	bufferDescription.RefreshRate.Denominator	= 1;
	bufferDescription.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDescription.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDescription.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;

	// describe SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDescription;
	ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDescription.BufferDesc			= bufferDescription;
	swapChainDescription.SampleDesc.Count	= 1;
	swapChainDescription.SampleDesc.Quality	= 0;
	swapChainDescription.BufferUsage		= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescription.BufferCount		= 1;
	swapChainDescription.OutputWindow       = window->getHandle();
	swapChainDescription.Windowed			= TRUE;
	swapChainDescription.SwapEffect			= DXGI_SWAP_EFFECT_DISCARD;

	// create swapChain
	hResult = D3D11CreateDeviceAndSwapChain(
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
		&d3d11DeviceContext
	);

	// create backBuffer
	ID3D11Texture2D* backBuffer;
	hResult = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	// create render target
	hResult = d3d11Device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	backBuffer->Release();

	return true;
}

bool D3DInterface::initializeScene(class Window* window)
{
	HRESULT hr;

	// compile shaders from shader file
	hr = D3DCompileFromFile(L"resource/shaders/VSTest.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &VS_Buffer, nullptr);
	hr = D3DCompileFromFile(L"resource/shaders/PSTest.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &PS_Buffer, nullptr);

	// create the shader objects
	hr = d3d11Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
	hr = d3d11Device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);

	// set vertex and pixel shaders
	d3d11DeviceContext->VSSetShader(VS, 0, 0);
	d3d11DeviceContext->PSSetShader(PS, 0, 0);

	// create vertex buffer
	Vertex vertex[] =
	{
		Vertex(-1.0f, -1.0f, 0.0f),
		Vertex( 0.0f,  1.0f, 0.0f),
		Vertex( 1.0f, -1.0f, 0.0f)
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
	hr = d3d11Device->CreateBuffer(&vertexBufferDescription, &vertexBufferData, &triangleVertBuffer);

	// create input layout
	layout = new D3D11_INPUT_ELEMENT_DESC[]
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA },
	};
	hr = d3d11Device->CreateInputLayout(layout, 1, VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), &vertLayout);

	return true;
}

void D3DInterface::releaseObjects()
{
	// release COM objects
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

void D3DInterface::update()
{
	updateBackgroundColor();
}

void D3DInterface::render()
{
	clear();
	draw();
	display();
}

void D3DInterface::updateBackgroundColor()
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

void D3DInterface::clear()
{
	// clear backbuffer to updated color
	const FLOAT backgroundColor[4] = { color.r, color.g, color.b, color.a };
	d3d11DeviceContext->ClearRenderTargetView(renderTargetView, backgroundColor);
}

void D3DInterface::draw()
{
	// draw scene
	drawTriangle();
}

void D3DInterface::display()
{
	// present backbuffer to screen
	swapChain->Present(0, 0);
}

void D3DInterface::drawTriangle()
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

	d3d11DeviceContext->Draw(3, 0);
}