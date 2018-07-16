#include "main.h"
#include "DirectX.h"

bool MainLoopFunc()
{
  return true;
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPWSTR lpCmdStr, int nCmd)
{
#if DEBUG_MODE
  //コンソール出力
  AllocConsole();
  freopen("CONOUT$", "w", stdout); //標準出力をコンソールにする
  freopen("CONIN$", "r", stdin);   //標準入力をコンソールにする
#endif

  //WinAPIの初期化
  if (winapi::WinApiInit(hInstance) == E_FAIL) return E_FAIL;

  //DirectXの初期化
  if (directx::DirectInit() == E_FAIL) return E_FAIL;

  //実際にウィンドウを描画
  ShowWindow(winapi::GetHwnd(), nCmd);

  //メインループ関数
  winapi::MainLoop(MainLoopFunc);
  
  //DirectXの開放
  directx::DirectRelease();

  //通常終了
  return winapi::SystemReturn();
}