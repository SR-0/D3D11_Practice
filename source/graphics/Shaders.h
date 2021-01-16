#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <d3d10.h>
#include <d3dcompiler.h>
#include <fstream>

class HLSLShader
{
public:

	HLSLShader();

	HLSLShader(
		LPCWSTR					pFileLocation, 
		const D3D_SHADER_MACRO* pDefines, 
		ID3DInclude*			pInclude,
		LPCSTR					pEntryPoint,
		LPCSTR					pTarget,
		UINT					flag1,
		UINT					flag2,
		ID3DBlob**				ppCode,
		ID3DBlob**				ppErrorMessages);

	~HLSLShader();

public:

	bool createHLSLFile(
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

	void createHLSLFileAndCompile(
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

public:

	void attachHLSLFile(
		LPCWSTR					pFileLocation, 
		const D3D_SHADER_MACRO* pDefines, 
		ID3DInclude*			pInclude,
		LPCSTR					pEntryPoint,
		LPCSTR					pTarget,
		UINT					flag1,
		UINT					flag2,
		ID3DBlob**				ppCode,
		ID3DBlob**				ppErrorMessages);

	void attachHLSLFileAndCompile(
		LPCWSTR					pFileLocation, 
		const D3D_SHADER_MACRO* pDefines, 
		ID3DInclude*			pInclude,
		LPCSTR					pEntryPoint,
		LPCSTR					pTarget,
		UINT					flag1,
		UINT					flag2,
		ID3DBlob**				ppCode,
		ID3DBlob**				ppErrorMessages);

public:

	void compile();

private:

	LPCWSTR					pFileLocation	= nullptr;
	const D3D_SHADER_MACRO* pDefines		= nullptr;
	ID3DInclude*			pInclude		= nullptr;
	LPCSTR					pEntryPoint		= nullptr;
	LPCSTR					pTarget			= nullptr;
	UINT					flag1			= 0;
	UINT					flag2			= 0;
	ID3DBlob**				ppCode			= nullptr;
	ID3DBlob**				ppErrorMessages	= nullptr;

private:

	std::ifstream input;
	std::ofstream output;

};

