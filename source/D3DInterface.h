#pragma once
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dcompiler.lib" )
#include <d3d11.h>

struct Color
{
	Color()
		:
		r(0.f),
		g(0.f),
		b(0.f),
		a(0.f)
	{}

	Color(float r, float g, float b, float a)
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
	Vector3f()
		:
		x(0.f),
		y(0.f),
		z(0.f)
	{}

	Vector3f(float x, float y, float z)
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
	Vector4f()
		:
		x(0.f),
		y(0.f),
		z(0.f),
		w(0.f)
	{}

	Vector4f(float x, float y, float z, float w)
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
	Vertex()
		:
		position(0.f, 0.f, 0.f)
	{}

	Vertex(float x, float y, float z)
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
	bool initializeScene();
	void updateScene();
	void drawScene();

private:

	IDXGISwapChain*				swapChain			= nullptr;
	ID3D11Device*				d3d11Device			= nullptr;
	ID3D11DeviceContext*		d3d11DeviceContext	= nullptr;
	ID3D11RenderTargetView*		renderTargetView	= nullptr;
	D3D11_INPUT_ELEMENT_DESC*	layout				= nullptr;

private:

	Color	color;
	Color	colorModifier;

};

