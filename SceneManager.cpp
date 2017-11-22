﻿//*****************************************************************************
//
// シーンマネジャー処理 [SceneManager.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "SceneManager.h"

#include "fstream"

using namespace std;

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
SceneManager::SceneManager()
{
	// クラスポインタ
	m_ResourcesManager = new ResourcesManager();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
SceneManager::~SceneManager()
{
	// クラスポインタ
	SAFE_RELEASE_CLASS_POINT(m_ResourcesManager);
}

//*****************************************************************************
//
// シンーの初期化
//
//*****************************************************************************
void SceneManager::InitScene(string name)
{
	m_SceneName = name;

	// コンソールにメッセージを出す
	cout << "///////////////////////////////" << endl;
	cout << "// Scene : " << m_SceneName << endl;
	cout << "///////////////////////////////" << endl << endl;
	
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void SceneManager::UpdateScene()
{

}

//*****************************************************************************
//
// シンーの終了処理
//
//*****************************************************************************
void SceneManager::UninitScene()
{

}

//*****************************************************************************
//
// ファイルからシンーの資源を読み込み
//
//*****************************************************************************
HRESULT SceneManager::LoadSceneFile(string name)
{
	// コンソールにメッセージを出す
	cout << "Loading " << name << endl;

	// 読み込みオブジェクトを作る
	ifstream fin;
	
	// ファイルを読み込み
	fin.open(name);

	// 読み込みは失敗した場合
	if (fin.fail())
	{
		// コンソールにメッセージを出す
		cout << "エラー[ 読み込み失敗 ]" << endl;
		return E_FAIL;
	}
	else
	{
		// コンソールにメッセージを出す
		cout << name << " ok!" << endl;
		char PathTemp[100];
		while (!fin.eof())
		{
			fin.getline(PathTemp, 100);
			cout << PathTemp << endl;
		}

		// 未完成
	}
}

//*****************************************************************************
//
// ファイルからシンーの資源を読み込み
//
//*****************************************************************************
void SceneManager::LoadScene()
{
	m_ResourcesManager->InitTextureList();
}

//*****************************************************************************
//
// リソースマネジメントを取得
//
//*****************************************************************************
ResourcesManager* SceneManager::GetResourcesManager()
{
	return m_ResourcesManager;
}