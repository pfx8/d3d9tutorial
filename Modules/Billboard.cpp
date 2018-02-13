//*****************************************************************************
//
// ビルボード処理 [billboard.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "billboard.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************


//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
BillBoard::BillBoard()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
BillBoard::~BillBoard()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexBillboard(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_BILLBOARD,			// ファイルの名前
								&g_pD3DTextureBillboard);	// 読み込むメモリー

	g_posBillboard = D3DXVECTOR3(0.0f, 18.0f, 0.0f);
	g_sclBillboard = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_moveBillboard = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 shadowPos = g_posBillboard;
	shadowPos.y -= 15;
	// 影の設定
	g_nIdxShadowBillboard = CreateShadow(shadowPos, BILLBOARD_SIZE_X, BILLBOARD_SIZE_Y);
	SetColorShadow(g_nIdxShadowBillboard, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	g_bEnableGravity = false;

	g_use = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBillboard(void)
{
	if(g_pD3DTextureBillboard != NULL)
	{// テクスチャの開放
		g_pD3DTextureBillboard->Release();
		g_pD3DTextureBillboard = NULL;
	}

	if(g_pD3DVtxBuffBillboard != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffBillboard->Release();
		g_pD3DVtxBuffBillboard = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBillboard(void)
{
	//D3DXVECTOR3 rotCamera;

	//// カメラの回転を取得
	//rotCamera = GetRotCamera();

	//if(GetKeyboardPress(DIK_LEFT))
	//{
	//	if(GetKeyboardPress(DIK_UP))
	//	{// 左前移動
	//		g_moveBillboard.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_BILLBOARD;
	//		g_moveBillboard.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_BILLBOARD;
	//	}
	//	else if(GetKeyboardPress(DIK_DOWN))
	//	{// 左後移動
	//		g_moveBillboard.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_BILLBOARD;
	//		g_moveBillboard.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_BILLBOARD;
	//	}
	//	else
	//	{// 左移動
	//		g_moveBillboard.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_BILLBOARD;
	//		g_moveBillboard.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_BILLBOARD;
	//	}
	//}
	//else if(GetKeyboardPress(DIK_RIGHT))
	//{
	//	if(GetKeyboardPress(DIK_UP))
	//	{// 右前移動
	//		g_moveBillboard.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_BILLBOARD;
	//		g_moveBillboard.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_BILLBOARD;
	//	}
	//	else if(GetKeyboardPress(DIK_DOWN))
	//	{// 右後移動
	//		g_moveBillboard.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_BILLBOARD;
	//		g_moveBillboard.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_BILLBOARD;
	//	}
	//	else
	//	{// 右移動
	//		g_moveBillboard.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_BILLBOARD;
	//		g_moveBillboard.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_BILLBOARD;
	//	}
	//}
	//else if(GetKeyboardPress(DIK_UP))
	//{// 前移動
	//	g_moveBillboard.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_BILLBOARD;
	//	g_moveBillboard.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_BILLBOARD;
	//}
	//else if(GetKeyboardPress(DIK_DOWN))
	//{// 後移動
	//	g_moveBillboard.x -= sinf(rotCamera.y) * VALUE_MOVE_BILLBOARD;
	//	g_moveBillboard.z -= cosf(rotCamera.y) * VALUE_MOVE_BILLBOARD;
	//}

	//if(GetKeyboardTrigger(DIK_SPACE))
	//{// ジャンプ
	//	if(g_bEnableGravity == true)
	//	{
	//		g_moveBillboard.y = VALUE_JUMP;
	//	}
	//}

	//g_posBillboard.x += g_moveBillboard.x;
	//g_posBillboard.z += g_moveBillboard.z;

	//g_moveBillboard.x += (0.0f - g_moveBillboard.x) * RATE_REGIST;
	//g_moveBillboard.z += (0.0f - g_moveBillboard.z) * RATE_REGIST;

	//if(g_bEnableGravity == true)
	//{
	//	g_posBillboard.y += g_moveBillboard.y;
	//	if(g_posBillboard.y < 9.0f)
	//	{
	//		g_posBillboard.y = 9.0f;
	//		g_moveBillboard.y *= RATE_REFRECT;
	//	}
	//	g_moveBillboard.y -= VALUE_GRAVITY;
	//}

	if (g_use == true)
	{
		// 範囲チェック
		if (g_posBillboard.x < -310.0f)
		{
			g_posBillboard.x = -310.0f;
			g_use = false;
		}
		else if (g_posBillboard.x > 310.0f)
		{
			g_posBillboard.x = 310.0f;
			g_use = false;
		}
		else if (g_posBillboard.z < -310.0f)
		{
			g_posBillboard.z = -310.0f;
			g_use = false;
		}
		else if (g_posBillboard.z > 310.0f)
		{
			g_posBillboard.z = 310.0f;
			g_use = false;
		}
		else
		{
			g_moveBillboard += g_moveBillboard*1.0f;
		}

		g_posBillboard.x += g_moveBillboard.x;
		g_posBillboard.z += g_moveBillboard.z;

		//SetVertexBillboard(g_posBillboard.x, g_posBillboard.z);

		//{// 影の設定
		//	SetPositionShadow(g_nIdxShadowBillboard, D3DXVECTOR3(g_posBillboard.x, 0.1f, g_posBillboard.z));

		//	float fSizeX = BILLBOARD_SIZE_X + (g_posBillboard.y - 9.0f) * 0.025f;
		//	if(fSizeX < BILLBOARD_SIZE_X)
		//	{
		//		fSizeX = BILLBOARD_SIZE_X;
		//	}
		//	float fSizeY = BILLBOARD_SIZE_Y + (g_posBillboard.y - 9.0f) * 0.025f;
		//	if(fSizeY < BILLBOARD_SIZE_Y)
		//	{
		//		fSizeY = BILLBOARD_SIZE_Y;
		//	}
		//	SetVertexShadow(g_nIdxShadowBillboard, fSizeX, fSizeY);

		//	float colA = (400.0f - (g_posBillboard.y - 9.0f)) / 800.0f;
		//	if(colA < 0.0f)
		//	{
		//		colA = 0.0f;
		//	}
		//	SetColorShadow(g_nIdxShadowBillboard, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
		//}

	}

	// 重力ON/OFF
	if (GetKeyboardTrigger(DIK_G))
	{
		g_bEnableGravity ^= 1;
	}

	PrintDebugProc("*** 重力 ***\n");
	PrintDebugProc("重力ON/OFF : G\n");
	PrintDebugProc("[重力 = ");
	if (g_bEnableGravity)
	{
		PrintDebugProc("ON]\n");
	}
	else
	{
		PrintDebugProc("OFF]\n");
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBillboard(void)
{
	if (g_use == true)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		D3DXMATRIX mtxView, mtxScale, mtxTranslate;

		// ラインティングを無効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// ビューマトリックスを取得
		mtxView = GetMtxView();

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldBillboard);

		// ポリゴンを正面に向ける
		g_mtxWorldBillboard._11 = mtxView._11;
		g_mtxWorldBillboard._21 = mtxView._12;
		g_mtxWorldBillboard._12 = mtxView._21;
		g_mtxWorldBillboard._31 = mtxView._13;
		g_mtxWorldBillboard._13 = mtxView._31;
		g_mtxWorldBillboard._22 = mtxView._22;
		g_mtxWorldBillboard._32 = mtxView._23;
		g_mtxWorldBillboard._23 = mtxView._32;
		g_mtxWorldBillboard._33 = mtxView._33;

		// スケールを反映
		D3DXMatrixScaling(&mtxScale, g_sclBillboard.x,
			g_sclBillboard.y,
			g_sclBillboard.z);
		D3DXMatrixMultiply(&g_mtxWorldBillboard,
			&g_mtxWorldBillboard, &mtxScale);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_posBillboard.x,
			g_posBillboard.y,
			g_posBillboard.z);
		D3DXMatrixMultiply(&g_mtxWorldBillboard,
			&g_mtxWorldBillboard, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffBillboard, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureBillboard);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// ラインティングを有効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_3D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffBillboard,	// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffBillboard->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBillboard(float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffBillboard->Unlock();
	}
}

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	g_posBillboard = pos;
	g_moveBillboard = move;

	g_use = true;
}