#pragma once
#include "main.h"

namespace winapi
{
//メインループ関数ポインタ
typedef bool(*MainLoopFunc)();

//WindowsAPIの初期化変数
HRESULT WinApiInit(HINSTANCE hInstance);

//メインループ処理
void MainLoop(MainLoopFunc main_loop_func);

//ウィンドウの幅取得
void GetWindowSize(int &width, int &height);

//システム終了の関数　注：メイン関数のリターンで返す値が戻り値として出力される
int SystemReturn();

const HWND GetHwnd();
}
