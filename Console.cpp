//*****************************************************************************
//
// コンソール処理 [Console.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Console.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Console::Console()
{
	// コンソールを初期化
	m_ConsoleStatus = AllocConsole();

	// コンソールのタイトルを設定する
	SetConsoleTitle(_T("Debug Output"));

	// コンソールにinput,outputを定義する
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Console::~Console()
{
	// もしコンソールがフリーされたら、m_ConsoleStatusはfalseになる
	//getchar();
	m_ConsoleStatus =  FreeConsole() & 1;
}

//*****************************************************************************
//
// コンソールの状態を取得
//
//*****************************************************************************
bool Console::GetConsoleStatue()
{
	return m_ConsoleStatus;
}