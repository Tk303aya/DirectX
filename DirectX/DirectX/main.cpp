#include "main.h"

void WinPro()
{

}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPWSTR lpCmdStr, int nCmd)
{
#if DEBUG_MODE
  //コンソール出力
  AllocConsole();
  freopen("CONOUT$", "w", stdout); //標準出力をコンソールにする
  freopen("CONIN$", "r", stdin);   //標準入力をコンソールにする
#endif
  MSG msg = {};
  HWND hWnd;
  WNDCLASSEX wndcls = 
  {

  };



  return msg.wParam;
}