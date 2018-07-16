#include "WindowAPI.h"
#include "DirectX.h"
#include <string>
namespace winapi
{
MSG Msg;                           //�E�B���h�E���b�Z�[�W�\����
HWND hWnd;                         //�E�B���h�E�n���h������
WNDCLASSEX WndCls;                 //�E�B���h�E�̃p�����[�^
LPCTSTR ClassName = _T("DirectX"); //�E�B���h�E��
int WndWidth  = 640;               //�E�B���h�E�̉���
int WndHeight = 480;               //�E�B���h�E�̏c��

//����������n
bool is_init = false;

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    case WM_QUIT:
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default:
      return DefWindowProc(hWnd, Msg, wParam, lParam);
      break;
  }
  return 0;
}

HRESULT WinApiInit(HINSTANCE hInstance)
{
  if (!is_init)
  {
    Msg = {};
    hWnd = {};
    WndCls =
    {
      sizeof(WNDCLASSEX),         //UINT        cbSize;         WNDCLASSEX�\���̂̃T�C�Y
                                  ///* Win 3.x */
      CS_HREDRAW | CS_VREDRAW,      //UINT        style;          �E�B���h�E�N���X�̃X�^�C��
      WinProc,                    //WNDPROC     lpfnWndProc;    �E�B���h�E�v���V�[�W���̃|�C���^
      0,                          //int         cbClsExtra;     �A�v���P�[�V�����Ɋ��蓖�Ă�]���ȃo�C�g��
      0,                          //int         cbWndExtra;     �E�B���h�E�N���X�ɂɊ��蓖�Ă�]���ȃo�C�g��
      hInstance,                  //HINSTANCE   hInstance;      �E�B���h�E�v���V�[�W�����܂ރC���X�^���X�ւ̃n���h��
      NULL,                       //HICON       hIcon;          �E�B���h�E�A�C�R���̃n���h��
      NULL,                       //HCURSOR     hCursor;        �J�[�\���̃n���h��
      (HBRUSH)(COLOR_WINDOW + 1), //HBRUSH      hbrBackground;  �o�b�N�O���E���h�u���V�̃n���h��
      NULL,                       //LPCWSTR     lpszMenuName;   ���j���[�̃��\�[�X���B���j���[�o�[�̑���ɕK�v
      ClassName,                  //LPCWSTR     lpszClassName;  �N���X�����ʂ��邽�߂̖��O
                                  ///* Win 4.0 */   
      NULL                        //HICON       hIconSm;        �������E�B���h�E�A�C�R���̃n���h��
    };

    //�쐬�����E�B���h�E�N���X�����W�X�^�ɓo�^
    HRESULT hr = RegisterClassEx(&WndCls);
    if (!hr)return E_FAIL;

    //�f�B�X�v���C�̑傫���擾
    RECT client_rect = {0,0,WndWidth,WndHeight}; //�N���C�A���g�T�C�Y�����߂邽�߂̋�`�\����
    AdjustWindowRect(&client_rect, WS_OVERLAPPEDWINDOW, FALSE);//�E�B���h�E�̑傫�������ۂɎ擾
    //�E�B���h�E�T�C�Y���烁�j���[�o�[���̍����������ăN���C�A���g�T�C�Y�����߂�
    int width = client_rect.right - client_rect.left;
    int height = client_rect.bottom - client_rect.top;
    //�X�N���[���T�C�Y���擾���ď�ɒ��S�ɔz�u�����悤�ɐݒ�
    int x = GetSystemMetrics(SM_CXSCREEN) / 2 - client_rect.right / 2;
    int y = GetSystemMetrics(SM_CYSCREEN) / 2 - client_rect.bottom / 2;

    //�E�B���h�E�̍쐬
    hWnd = CreateWindow(
      ClassName,              //_In_opt_ LPCWSTR lpClassName,   �o�^����Ă���N���X��
      ClassName,              //_In_opt_ LPCWSTR lpWindowName,  �E�B���h�E��
      WS_OVERLAPPEDWINDOW,    //_In_ DWORD dwStyle,             �E�B���h�E�̃X�^�C��
      x,                      //_In_ int X,                     �f�B�X�v���C�̃X�^�[�g�w���W
      y,                      //_In_ int Y,                     �f�B�X�v���C�̃X�^�[�g�x���W
      width,                  //_In_ int nWidth,                �E�B���h�E�̉���
      height,                 //_In_ int nHeight,               �E�B���h�E�̏c��
      NULL,                   //_In_opt_ HWND hWndParent,       �쐬����Ă���e�E�C���h�E�̃n���h��
      NULL,                   //_In_opt_ HMENU hMenu,           ���j���[�o�[�̃n���h��
      hInstance,              //_In_opt_ HINSTANCE hInstance,   �E�B���h�E�Ɋ֘A�t������C���X�^���X�n���h��
      NULL                    //_In_opt_ LPVOID lpParam         �ǉ��̃A�v���P�[�V�����f�[�^
    );
    if (!hWnd) return E_FAIL;

    is_init = true;
  }
  return S_OK;
}
//�E�B���h�E���b�Z�[�W����������\����
bool ProcessMessage()
{
  //�E�B���h�E�v���V�[�W���̃��b�Z�[�W����������
  if (PeekMessage(&Msg,     //_Out_ LPMSG lpMsg,        ���b�Z�[�W���n���h��
                  NULL,     //_In_opt_ HWND hWnd,       �E�B���h�E�̃n���h���ANULL�Ńf�t�H���g���Ă΂��
                  0,        //_In_ UINT wMsgFilterMin,  �擾�Ώۂ̃��b�Z�[�W�̍ŏ��l��ݒ肷��
                  0,        //_In_ UINT wMsgFilterMax,  �擾�Ώۂ̃��b�Z�[�W�̍ő�l��ݒ肷��
                  PM_REMOVE //_In_ UINT wRemoveMsg      �폜�I�v�V�����@PM_REMOVE�Ń��b�Z�[�W���폜����APM_NOREMOVE�ō폜���Ȃ�
  ))
  {
    //�����Ă����L�[�{�[�h���b�Z�[�W�̑召�����ɕ��ނ���
    TranslateMessage(&Msg); //_In_ CONST MSG *lpMsg
    //���b�Z�[�W���E�B���h�E�Y�v���V�[�W���ɑ���
    DispatchMessage(&Msg);  //_In_ CONST MSG *lpMsg
  }
  if (Msg.message == WM_QUIT)
  {
    return false;
  }
  return true;
}

void MainLoop(MainLoopFunc main_loop_func)
{
  while (ProcessMessage() & directx::ScreenStart() & main_loop_func() & directx::ScreenEnd())
  {}
}
void GetWindowSize(int &width, int &height)
{
  if (width) width = WndWidth;
  if (height) height = WndHeight;
}
int SystemReturn()
{
  return Msg.message;
}
const HWND GetHwnd()
{
  return hWnd;
}
}