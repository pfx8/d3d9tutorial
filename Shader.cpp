//*****************************************************************************
//
// Shader処理 [Shader.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Shader.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Shader::Shader()
{
	m_shaderBuffer = NULL;
	m_errorBuffer = NULL;
	m_vertexShader = NULL;
	m_constTable = NULL;

	m_WVPMatrixHandle = NULL;
	m_LightDirectionHandle = NULL;
	m_Scalar = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Shader::~Shader()
{
	SAFE_RELEASE_POINT(m_shaderBuffer);
	SAFE_RELEASE_POINT(m_errorBuffer);
	SAFE_RELEASE_POINT(m_vertexShader);
	SAFE_RELEASE_POINT(m_constTable);
}

//*****************************************************************************
//
// シェーダーファイルを読み込む
//
//*****************************************************************************
HRESULT Shader::LoadShaderFile()
{
	D3DVERTEXELEMENT9 MorphMeshDecl[] =
	{
		//1st stream is for source mesh - position, normal, texcoord
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },

		//2nd stream is for target mesh - position, normal
		{ 1,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 1 },
		{ 1, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   1 },
		D3DDECL_END()
	};

	HRESULT hr = D3DXCompileShaderFromFile(
		"Shader/Vertex.hlsl",
		0,
		0,
		"SetColor",		// シェーダーの入り口関数
		"vs_1_0",			// コンパイル ターゲットを含む文字列へのポインタ???
		D3DXSHADER_DEBUG,	// ンパイル オプション
		&m_shaderBuffer,	// シェーダーバッファ
		&m_errorBuffer,	// エラーバッファ
		&m_constTable);	// 定数表

	if (m_errorBuffer)		// エラーを出す
	{
		std::cout << "Error: Shader->m_errorBuffer" << std::endl;
		SAFE_RELEASE_POINT(m_errorBuffer);
		return E_FAIL;
	}

	if (FAILED(hr))	// エラーを出す
	{
		std::cout << "Error: Shader->LoadShader" << std::endl;
		return E_FAIL;
	}

	// 頂点シェーダーができた
	hr = GetDevice()->CreateVertexShader((DWORD*)m_shaderBuffer->GetBufferPointer(), &m_vertexShader);

	if (FAILED(hr))	// エラーを出す
	{
		std::cout << "Error: Shader->CreateVertexShader" << std::endl;
		return E_FAIL;
	}

	SAFE_RELEASE_POINT(m_shaderBuffer);	// シェーダーバッファをリリース

	// シェーダーファイル中の変数を取得
	m_WVPMatrixHandle = m_constTable->GetConstantByName(0, "WVPMatrix");	// WVPマトリックス
	m_LightDirectionHandle = m_constTable->GetConstantByName(0, "LightDirection");	// 乱反射光
	m_Scalar = m_constTable->GetConstantByName(0, "Scalar");	// モーフィング数値

	m_constTable->SetVector(GetDevice(), m_LightDirectionHandle, &D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f));
	m_constTable->SetDefaults(GetDevice());	// デフォルト設定

	return S_OK;
}