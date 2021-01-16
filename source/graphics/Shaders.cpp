#include "Shaders.h"

HLSLShader::HLSLShader()
{
}

HLSLShader::HLSLShader(
	LPCWSTR					pFileLocation, 
	const D3D_SHADER_MACRO* pDefines, 
	ID3DInclude*			pInclude,
	LPCSTR					pEntryPoint,
	LPCSTR					pTarget,
	UINT					flag1,
	UINT					flag2,
	ID3DBlob**				ppCode,
	ID3DBlob**				ppErrorMessages)
	:
	pFileLocation(pFileLocation),
	pDefines(pDefines),
	pInclude(pInclude),
	pEntryPoint(pEntryPoint),
	pTarget(pTarget),
	flag1(flag1),
	flag2(flag2),
	ppCode(ppCode),
	ppErrorMessages(ppErrorMessages)
{
	compile();
}

HLSLShader::~HLSLShader()
{
}

bool HLSLShader::createHLSLFile(
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
	std::string				HLSLCode)
{
	this->pFileLocation		= pNewFileLocation;
	this->pDefines			= pDefines; 
	this->pInclude			= pInclude;
	this->pEntryPoint		= pEntryPoint;
	this->pTarget			= pTarget;
	this->flag1				= flag1;
	this->flag2				= flag2;
	this->ppCode			= ppCode;
	this->ppErrorMessages	= ppErrorMessages;

	LPCWSTR path = pNewFileLocation;
	
	input = std::ifstream(pNewFileLocation);

	if (input.is_open())
	{
		input.close();

		if (overridePreviousCode)
		{
			output.open(pNewFileLocation);

			while (output.is_open())
			{
				for (unsigned int i = 0; i < HLSLCode.size(); i++)
				{
					output << HLSLCode[i];
				}

				output.close();
			}
		}
		else
		{
			MessageBoxEx(0, L"Shader File Creation - Failed (Already exists)\n\nIgnore by changing 'overridePreviousCode' argument to 'true' or\nremove last argument in 'createHLSLFile()' function parameters \n to attach existing HLSL shader file", L"Warning", MB_OK, CAL_GREGORIAN_XLIT_ENGLISH);
		}
	}
	else
	{
		output.open(pNewFileLocation);

		while (output.is_open())
		{
			for (unsigned int i = 0; i < HLSLCode.size(); i++)
			{
				output << HLSLCode[i];
			}

			output.close();
		}
	}

	return true;
}

void HLSLShader::createHLSLFileAndCompile(
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
	std::string				HLSLCode)
{
	createHLSLFile(
		pNewFileLocation,
		pDefines,
		pInclude,
		pEntryPoint,
		pTarget,
		flag1,
		flag2,
		ppCode,
		ppErrorMessages,
		overridePreviousCode,
		HLSLCode);

	compile();
}

void HLSLShader::attachHLSLFile(
	LPCWSTR					pFileLocation, 
	const D3D_SHADER_MACRO* pDefines, 
	ID3DInclude*			pInclude,
	LPCSTR					pEntryPoint,
	LPCSTR					pTarget,
	UINT					flag1,
	UINT					flag2,
	ID3DBlob**				ppCode,
	ID3DBlob**				ppErrorMessages)
{
	this->pFileLocation		= pFileLocation; 
	this->pDefines			= pDefines; 
	this->pInclude			= pInclude;
	this->pEntryPoint		= pEntryPoint;
	this->pTarget			= pTarget;
	this->flag1				= flag1;
	this->flag2				= flag2;
	this->ppCode			= ppCode;
	this->ppErrorMessages	= ppErrorMessages;
}

void HLSLShader::attachHLSLFileAndCompile(
	LPCWSTR					pFileLocation, 
	const D3D_SHADER_MACRO* pDefines, 
	ID3DInclude*			pInclude,
	LPCSTR					pEntryPoint,
	LPCSTR					pTarget,
	UINT					flag1,
	UINT					flag2,
	ID3DBlob**				ppCode,
	ID3DBlob**				ppErrorMessages)
{
	attachHLSLFile(
		pFileLocation,
		pDefines,
		pInclude,
		pEntryPoint,
		pTarget,
		flag1,
		flag2,
		ppCode,
		ppErrorMessages);

	compile();
}

void HLSLShader::compile()
{
	HRESULT hResult = D3DCompileFromFile(
		pFileLocation,
		pDefines,
		pInclude,
		pEntryPoint,
		pTarget,
		flag1,
		flag2,
		ppCode,
		ppErrorMessages);
}
