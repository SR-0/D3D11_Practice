#pragma once

// lib links
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3d10.lib" )
#pragma comment( lib, "d3dcompiler.lib" )

// d3d includes
#include <d3d11.h>
#include <d3dcompiler.h>

// local includes
#include "CustomTypes.h"

class Graphics
{
public: // constructors and destructors

	Graphics(class Window* window);
	~Graphics();

public: // all initialization/creation, setup, and destruction encapsulated and called by Graphics() and ~Graphics()

	void create(class Window* window);
	void setup();
	void destroy();

private: // core specific initialization/creation functions called by 'create()'

	bool createGraphics(class Window* window);
	bool createScene(class Window* window);

private: // specific initialization/creation functions called by 'createGraphics()'

	void createBufferDescription(
		unsigned int				width,
		unsigned int				height,
		unsigned int				refreshRateNumerator,
		unsigned int				refreshRateDenominator,
		DXGI_FORMAT					format,
		DXGI_MODE_SCANLINE_ORDER	scanlineOrder,
		DXGI_MODE_SCALING			scaling);

	void createSwapChainDescription(
		DXGI_MODE_DESC		bufferDescription,
		unsigned int		sampleDescriptionCount,
		unsigned int		sampleDescriptionQuality,
		DXGI_USAGE			bufferUsage,
		unsigned int		bufferCount,
		HWND				outputWindow,
		BOOL				isWindowed,
		DXGI_SWAP_EFFECT	swapEffect);

	void createDeviceAndSwapChain(
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
		ID3D11DeviceContext**   ppImmediateContext);

	void createBackBuffer(UINT buffer, REFIID riid, void** ppSurface);

	void createRenderTargetView(
		ID3D11Resource*					pResource,
		D3D11_RENDER_TARGET_VIEW_DESC*	pDescription,
		ID3D11RenderTargetView**		ppRenderTargetView);

private: // specific initialization/creation functions called by 'createScene()'

	void createInputLayout();

private: // specific setup functions called by 'setup()'

	// empty atm

private: // core specific destruction functions called by 'destroy()'

	void destroyCOMObjects();

public: // all update & render encapsulation

	void update(); 
	void render(); 

public: // specific update functions called by 'update()'

	void updateBackgroundColor();

public: // specific render functions called by 'render()'

	void clear();
	void draw();
	void display();

public: // specific draw functions called by 'draw()'

	void drawTriangle();

private: // all DXGI decription objects

	DXGI_MODE_DESC			bufferDescription;
	DXGI_SWAP_CHAIN_DESC	swapChainDescription;

private: // all D3D11/D3D10 core objects

	ID3D11Texture2D*			backBuffer			= nullptr;
	IDXGISwapChain*				swapChain			= nullptr;
	ID3D11Device*				d3d11Device			= nullptr;
	ID3D11DeviceContext*		d3d11DeviceContext	= nullptr;
	ID3D11RenderTargetView*		renderTargetView	= nullptr;
	ID3D11Buffer*				triangleVertBuffer	= nullptr;
	ID3D11Buffer*				rectangleVertBuffer	= nullptr;
	ID3D11VertexShader*			VS					= nullptr;
	ID3D11PixelShader*			PS					= nullptr;
	ID3D10Blob*                 VS_Buffer			= nullptr;
	ID3D10Blob*					PS_Buffer			= nullptr;
	ID3D11InputLayout*          vertLayout			= nullptr;

private: // misc variables/objects

	
	Color	color;
	Color	colorModifier;
	HRESULT	hResult;

};