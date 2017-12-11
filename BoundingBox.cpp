﻿//*****************************************************************************
//
// バウンディングボックス処理[BoundingBox.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "BoundingBox.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
BoundingBox::BoundingBox()
{
	m_pos  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl  = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_indexBuffer = NULL;
	m_vertexBuffer = NULL;
	m_vertexDecl = NULL;

	m_isBoundingBoxDraw = true;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
BoundingBox::~BoundingBox()
{
	// ポインタ
	RELEASE_POINT(m_indexBuffer);
	RELEASE_POINT(m_vertexBuffer);
	RELEASE_POINT(m_vertexDecl);
}

//*****************************************************************************
//
// 幅、高さ、奥行きによって長方体を作り
//
//*****************************************************************************
void BoundingBox::InitBox(int width, int height, int depth, float alpha)
{
	m_size = D3DXVECTOR3((float)width, (float)height, (float)depth);
	m_alpha = alpha;

	MakeVertex();
}

//*****************************************************************************
//
// 長方体頂点を設定
//
//*****************************************************************************
HRESULT BoundingBox::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVERTEXELEMENT9 boundingBoxDecl[] =	// 頂点データのレイアウトを定義
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL   },
		{ 0, 24, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR    },
		{ 0, 40, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD },
		D3DDECL_END()
	};
	

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(8 * sizeof(VERTEX_3D_NT), 0, FVF_VERTEX_3D_NT, D3DPOOL_DEFAULT, &m_vertexBuffer, NULL)))
	{
		std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	// 頂点作成
	VERTEX_3D_NT vertex[] =
	{
		// 座標、法線、diffuse
		{ D3DXVECTOR3(-m_size.x / 2,  m_size.y / 2, -m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) },
		{ D3DXVECTOR3(-m_size.x / 2,  m_size.y / 2,  m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) },
		{ D3DXVECTOR3( m_size.x / 2,  m_size.y / 2,  m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) },
		{ D3DXVECTOR3( m_size.x / 2,  m_size.y / 2, -m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) },
		{ D3DXVECTOR3(-m_size.x / 2,  0,            -m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) },
		{ D3DXVECTOR3(-m_size.x / 2,  0,             m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) },
		{ D3DXVECTOR3( m_size.x / 2,  0,             m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) },
		{ D3DXVECTOR3( m_size.x / 2,  0,            -m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) }
	};

	VOID* VertexBuffer;	// 頂点バッファポインタ作成

	// 頂点データの範囲をロックして頂点バッファメモリへのポインタを取得する
	if (FAILED(m_vertexBuffer->Lock(0, sizeof(vertex), (void**)&VertexBuffer, 0)))
	{
		std::cout << "[Error] 頂点バッファがロックできない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}
	memcpy(VertexBuffer, vertex, sizeof(vertex));	// 作成された頂点を臨時ポインタの中に入れる
	m_vertexBuffer->Unlock();					// 頂点データをアンロックする


	//オブジェクトの頂点インデックスバッファを生成
	if (FAILED(pDevice->CreateIndexBuffer(36 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, NULL)))
	{
		std::cout << "[Error] 頂点インデクスが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	
	WORD* vertexIndex = NULL;	// イデックスの中身を埋める
	m_indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// インデックス データのある一定範囲をロックし、そのインデックス バッファー メモリーへのポインターを取得する

	// 底面(上)
	vertexIndex[0] = 0, vertexIndex[1] = 1, vertexIndex[2] = 2;
	vertexIndex[3] = 0, vertexIndex[4] = 2, vertexIndex[5] = 3;

	// 正面
	vertexIndex[6] = 0, vertexIndex[7] = 3, vertexIndex[8] = 7;
	vertexIndex[9] = 0, vertexIndex[10] = 7, vertexIndex[11] = 4;

	// 侧面(左)
	vertexIndex[12] = 0, vertexIndex[13] = 4, vertexIndex[14] = 5;
	vertexIndex[15] = 0, vertexIndex[16] = 5, vertexIndex[17] = 1;

	// 侧面(右)
	vertexIndex[18] = 2, vertexIndex[19] = 6, vertexIndex[20] = 7;
	vertexIndex[21] = 2, vertexIndex[22] = 7, vertexIndex[23] = 3;

	// 背面
	vertexIndex[24] = 2, vertexIndex[25] = 5, vertexIndex[26] = 6;
	vertexIndex[27] = 2, vertexIndex[28] = 1, vertexIndex[29] = 5;

	// 底面(下)
	vertexIndex[30] = 4, vertexIndex[31] = 6, vertexIndex[32] = 5;
	vertexIndex[33] = 4, vertexIndex[34] = 7, vertexIndex[35] = 6;

	// インデックス データのロックを解除する
	m_indexBuffer->Unlock();

	return S_OK;
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void BoundingBox::SetWorldMatrix(D3DXMATRIX& mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリクスの初期化
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
}

//*****************************************************************************
//
// テクスチャを描画する
//
//*****************************************************************************
void BoundingBox::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(VERTEX_3D_NT));	// 頂点バッファをデバイスのデータストリームにバイナリ
	pDevice->SetFVF(FVF_VERTEX_3D_NT);										// 頂点フォーマットの設定
	pDevice->SetIndices(m_indexBuffer);										// 頂点イデックスの設定
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 17, 0, 16);		// バウンディングボックスの描画
}

//*****************************************************************************
//
// 当たり判定(長方体)
//
//*****************************************************************************
//bool BoundingBox::CheckHitBB(Character* Object)
//{
//
//}