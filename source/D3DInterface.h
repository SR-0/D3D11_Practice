#pragma once
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3d10.lib" )
#pragma comment( lib, "d3dcompiler.lib" )
#include <d3d11.h>
#include <d3dcompiler.h>

struct Color
{
	Color(
		float r = 0.f, 
		float g = 0.f, 
		float b = 0.f, 
		float a = 0.f)
		:
		r(r),
		g(g),
		b(b),
		a(a)
	{}

	float	r;
	float	g;
	float	b;
	float   a;
};

struct Vector3f
{
	Vector3f(
		float x = 0.f, 
		float y = 0.f, 
		float z = 0.f)
		:
		x(x),
		y(y),
		z(z)
	{}

	float	x;
	float	y;
	float	z;
};

struct Vector4f
{
	Vector4f(
		float x = 0.f, 
		float y = 0.f, 
		float z = 0.f, 
		float w = 0.f)
		:
		x(x),
		y(y),
		z(z),
		w(w)
	{}

	float	x;
	float	y;
	float	z;
	float	w;
};

struct Vertex
{
	Vertex(
		float x = 0.f, 
		float y = 0.f, 
		float z = 0.f)
		:
		position(x, y, z)
	{}

	Vector3f position;
};

class D3DInterface
{
public:

	D3DInterface(class Window* window);
	~D3DInterface();

private:

	DXGI_MODE_DESC createBufferDescription(
		unsigned int				width,
		unsigned int				height,
		unsigned int				refreshRateNumerator,
		unsigned int				refreshRateDenominator,
		DXGI_FORMAT					DXGIFormat,
		DXGI_MODE_SCANLINE_ORDER 	DXGIMScanlineOrder,
		DXGI_MODE_SCALING			DXGIMScaling);

	DXGI_SWAP_CHAIN_DESC createSwapChainDescription(
		DXGI_MODE_DESC&		bufferDescription,
		unsigned int		sampleDescriptionCount,
		unsigned int		sampleDescriptionQuality,
		DXGI_USAGE			DXGIUsage,
		unsigned int		bufferCount,
		HWND				hWnd,
		BOOL				isWindowed,
		DXGI_SWAP_EFFECT	DXGISwapEffect);

public:

	bool initializeD3DApp(class Window* window);
	void releaseObjects();
	bool initializeScene(class Window* window);
	void updateScene();
	void drawScene();

public:

	void sceneUpdate_DrawColorChange();
	void sceneUpdate_DrawTriangle();

private:

	IDXGISwapChain*				swapChain			= nullptr;
	ID3D11Device*				d3d11Device			= nullptr;
	ID3D11DeviceContext*		d3d11DeviceContext	= nullptr;
	ID3D11RenderTargetView*		renderTargetView	= nullptr;
	ID3D11Buffer*				triangleVertBuffer	= nullptr;
	ID3D11VertexShader*			VS					= nullptr;
	ID3D11PixelShader*			PS					= nullptr;
	ID3D10Blob*                 VS_Buffer			= nullptr;
	ID3D10Blob*					PS_Buffer			= nullptr;
	ID3D11InputLayout*          vertLayout			= nullptr;

public:

	D3D11_INPUT_ELEMENT_DESC*	layout		= nullptr;
	UINT						numElements	= 0;

private:

	Color color;
	Color colorModifier;

};

