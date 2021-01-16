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
public:

	Graphics(class Window* window);
	~Graphics();

public: 
	
	/* 
		all creation/initialization, setup, update, render, and 
		destruction related functions will be called by these 
		five functions which are in turn going to be called by 
		Graphics() and ~Graphics() constructor and deconstructor
		excluding update() and render() functions which are meant
		to be called after creation in specified game/application loop

		|
		|
		V
	*/

	void create(class Window* window);
	void setup();
	void update(); 
	void render(); 
	void destroy();

private:

	/*
		all specific core creation/initialization functions called by the core 'create()' function

		|
		|
		V
	*/

	bool createGraphics(class Window* window);
	bool createShaders();
	bool createScene(class Window* window);

private:

	/*
		all specific core setup functions called by the core 'setup()' function

		|
		|
		V
	*/

	void setupGraphics();
	void setupShaders();
	void setupScene();

public:

	/*
		all specific core update functions called by the core 'update()' function

		|
		|
		V
	*/

	void updateGraphics();
	void updateShaders();
	void updateScene();

public:

	/*
		all specific render functions called by the core 'render()' function

		|
		|
		V
	*/

	void clear();
	void draw();
	void display();

private:

	/*
		all specific destroy functions called by the core 'destroy()' function

		|
		|
		V
	*/

	void destroyGraphics();
	void destroyShaders();
	void destroyScene();

private:

	/*
		all specific creation/initialization functions called by the 'createGraphics()' function

		|
		|
		V
	*/

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

private:

	/*
		all specific creation/initialization functions called by the 'createShaders()' function

		|
		|
		V
	*/

	void createHLSLShader(
		class HLSLShader*		pHLSLShader,
		LPCWSTR					pFileLocation, 
		const D3D_SHADER_MACRO* pDefines, 
		ID3DInclude*			pInclude,
		LPCSTR					pEntryPoint,
		LPCSTR					pTarget,
		UINT					flag1,
		UINT					flag2,
		ID3DBlob**				ppCode,
		ID3DBlob**				ppErrorMessages);

	void createHLSLShader(
		class HLSLShader*		pHLSLShader,
		LPCWSTR					pNewFileLocation, 
		const D3D_SHADER_MACRO* pDefines, 
		ID3DInclude*			pInclude,
		LPCSTR					pEntryPoint,
		LPCSTR					pTarget,
		UINT					flag1,
		UINT					flag2,
		ID3DBlob**				ppCode,
		ID3DBlob**				ppErrorMessages,
		bool					overridePreviousCode,
		std::string				HLSLCode);

private:

	/*
		all specific creation/initialization functions called by the 'createScene()' function

		|
		|
		V
	*/

	void createAndAttachVertexShader(
		const void*				pShaderByteCode, 
		SIZE_T					byteCodeLength, 
		ID3D11ClassLinkage*		pClassLinkage,
		ID3D11VertexShader**	ppVertexShader);

	void createAndAttachPixelShader(
		const void*				pShaderByteCode, 
		SIZE_T					byteCodeLength, 
		ID3D11ClassLinkage*		pClassLinkage,
		ID3D11PixelShader**		ppPixelShader);

	void createVertexBuffer(Vertex vertex[]);

	void createInputLayout();

public: // specific update functions called by 'updateScene()'

	/*
		all specific update functions called by the 'updateScene()' function

		|
		|
		V
	*/

	void updateBackgroundColor();

public:

	/*
		all specific draw functions called by the 'draw()' function

		|
		|
		V
	*/

	void drawTriangle();

private: // DXGI decription objects

	DXGI_MODE_DESC			bufferDescription;
	DXGI_SWAP_CHAIN_DESC	swapChainDescription;

private: // D3D11/D3D10 core objects

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

private: // HLSLShader objects

	// vertex shaders
	class HLSLShader* vertexShader1;

	// pixel shaders
	class HLSLShader* pixelShaderRed;
	class HLSLShader* pixelShaderBlue;
	class HLSLShader* pixelShaderGreen;

private: // misc variables/objects
	
	Color	color;
	Color	colorModifier;
	HRESULT	hResult;

};