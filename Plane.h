//*****************************************************************************
//
// 平面処理[Plane.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _PLANE_H_
#define _PLANE_H_

#include "Engine.h"
#include "Shader.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Plane
{
private:
	IDirect3DVertexDeclaration9* m_vertexDecl;	// 頂点シェーダー宣言
	LPDIRECT3DVERTEXBUFFER9	m_vertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_indexBuffer;	// 頂点インデックスバッファ
	
	//HRESULT MakeVertex(int width, int height);	// 頂点作成
	HRESULT MakeVertexDecl(int width, int height);	// 頂点宣言(Shader)
public:
	D3DXVECTOR3		m_pos;	// 位置
	D3DXVECTOR3		m_rot;	// 回転
	D3DXVECTOR3		m_scl;	// 拡大縮小
	LPDIRECT3DTEXTURE9			m_fieldTexture;	// フィールドテクスチャ

	Plane();
	~Plane();

	void InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 size);	// 座標を設定
	//void Draw();	// テクスチャを描画する
	void Draw(Shader* shader);	// テクスチャを描画する(PixelShader)
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);	// 臨時ーーワールド変換
};
#endif // !_PLANE_H_
