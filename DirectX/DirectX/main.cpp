#include "main.h"

void WinPro()
{

}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPWSTR lpCmdStr, int nCmd)
{
#if DEBUG_MODE
  //�R���\�[���o��
  AllocConsole();
  freopen("CONOUT$", "w", stdout); //�W���o�͂��R���\�[���ɂ���
  freopen("CONIN$", "r", stdin);   //�W�����͂��R���\�[���ɂ���
#endif
  MSG msg = {};
  HWND hWnd;
  WNDCLASSEX wndcls = 
  {

  };



  return msg.wParam;
}