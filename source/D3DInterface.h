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


class D3DInterface
{
public: // constructors and destructors

	D3DInterface(class Window* window);
	~D3DInterface();

public: // all initialization, setup, and destruction

	void initialize(class Window* window);
	void setup();
	void destruct();

private: // specific initialization functions

	bool initializeD3D(class Window* window);		// initialize
	bool initializeScene(class Window* window);		// setup

private: // specific setup functions

	// empty atm

private: // specific destruction functions

	void releaseObjects();							// destruct

public: // all update & render funcitons

	void update(); 
	void render(); 

public: // specific update functions

	void updateBackgroundColor();

public: // specific render functions

	void clear();
	void draw();
	void display();

public: // specific draw functions

	void drawTriangle();

private: // all COM objects

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
	D3D11_INPUT_ELEMENT_DESC*	layout				= nullptr;

private: // misc variables

	Color color;
	Color colorModifier;

};