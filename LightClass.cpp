﻿//*****************************************************************************
//
// ライトクラス [LightClass.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "LightClass.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Light::Light()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Light::~Light()
{

}

//*****************************************************************************
//
// 
//
//*****************************************************************************
Light::Light(LightType type)
{
	ChangeLight(type);
}

//*****************************************************************************
//
// 
//
//*****************************************************************************
void Light::ChangeLight(LightType type)
{
	// ライト構造体を初期化する
	static D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));

	switch (type)
	{
	case LT_PointLight:
		light.Type = D3DLIGHT_POINT;
		light.Ambient = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
		light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		light.Position = D3DXVECTOR3(0.0f, 200.0f, 0.0f);
		light.Attenuation0 = 1.0f;
		light.Attenuation1 = 0.0f;
		light.Attenuation2 = 0.0f;
		light.Range = 300.0f;
		break;
	case LT_DirectionalLight:
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		light.Direction = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		break;
	case LT_SpotLight:
		light.Type = D3DLIGHT_SPOT;
		light.Position = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
		light.Direction = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
		light.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);
		light.Attenuation0 = 1.0f;
		light.Attenuation1 = 0.6f;
		light.Attenuation2 = 0.3f;
		light.Range = 300.0f;
		light.Falloff = 0.1f;
		light.Phi = D3DX_PI / 3.0f;
		light.Theta = D3DX_PI / 6.0f;
		break;
	}

	// ライトを設定
	GetDevice()->SetLight(0, &light);

	// ライトオン
	GetDevice()->LightEnable(0, true);

	// 環境光を設定
	GetDevice()->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(36, 36, 36));
}