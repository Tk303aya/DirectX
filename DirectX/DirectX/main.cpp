#include "main.h"
#include "DirectX.h"

bool MainLoopFunc()
{
  return true;
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPWSTR lpCmdStr, int nCmd)
{
#if DEBUG_MODE
  //�R���\�[���o��
  AllocConsole();
  freopen("CONOUT$", "w", stdout); //�W���o�͂��R���\�[���ɂ���
  freopen("CONIN$", "r", stdin);   //�W�����͂��R���\�[���ɂ���
#endif

  //WinAPI�̏�����
  if (winapi::WinApiInit(hInstance) == E_FAIL) return E_FAIL;

  //DirectX�̏�����
  if (directx::DirectInit() == E_FAIL) return E_FAIL;

  //���ۂɃE�B���h�E��`��
  ShowWindow(winapi::GetHwnd(), nCmd);

  //���C�����[�v�֐�
  winapi::MainLoop(MainLoopFunc);
  
  //DirectX�̊J��
  directx::DirectRelease();

  //�ʏ�I��
  return winapi::SystemReturn();
}