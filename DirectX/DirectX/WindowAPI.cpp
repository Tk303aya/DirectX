#include "WindowAPI.h"
#include "DirectX.h"
#include <string>
namespace winapi
{
MSG Msg;                           //ウィンドウメッセージ構造体
HWND hWnd;                         //ウィンドウハンドル識別
WNDCLASSEX WndCls;                 //ウィンドウのパラメータ
LPCTSTR ClassName = _T("DirectX"); //ウィンドウ名
int WndWidth  = 640;               //ウィンドウの横幅
int WndHeight = 480;               //ウィンドウの縦幅

//初期化制御系
bool is_init = false;

//ウィンドウプロシージャ
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
      sizeof(WNDCLASSEX),         //UINT        cbSize;         WNDCLASSEX構造体のサイズ
                                  ///* Win 3.x */
      CS_HREDRAW | CS_VREDRAW,      //UINT        style;          ウィンドウクラスのスタイル
      WinProc,                    //WNDPROC     lpfnWndProc;    ウィンドウプロシージャのポインタ
      0,                          //int         cbClsExtra;     アプリケーションに割り当てる余分なバイト数
      0,                          //int         cbWndExtra;     ウィンドウクラスにに割り当てる余分なバイト数
      hInstance,                  //HINSTANCE   hInstance;      ウィンドウプロシージャを含むインスタンスへのハンドル
      NULL,                       //HICON       hIcon;          ウィンドウアイコンのハンドル
      NULL,                       //HCURSOR     hCursor;        カーソルのハンドル
      (HBRUSH)(COLOR_WINDOW + 1), //HBRUSH      hbrBackground;  バックグラウンドブラシのハンドル
      NULL,                       //LPCWSTR     lpszMenuName;   メニューのリソース名。メニューバーの操作に必要
      ClassName,                  //LPCWSTR     lpszClassName;  クラスを識別するための名前
                                  ///* Win 4.0 */   
      NULL                        //HICON       hIconSm;        小さいウィンドウアイコンのハンドル
    };

    //作成したウィンドウクラスをレジスタに登録
    HRESULT hr = RegisterClassEx(&WndCls);
    if (!hr)return E_FAIL;

    //ディスプレイの大きさ取得
    RECT client_rect = {0,0,WndWidth,WndHeight}; //クライアントサイズを求めるための矩形構造体
    AdjustWindowRect(&client_rect, WS_OVERLAPPEDWINDOW, FALSE);//ウィンドウの大きさを実際に取得
    //ウィンドウサイズからメニューバー等の差分を引いてクライアントサイズを求める
    int width = client_rect.right - client_rect.left;
    int height = client_rect.bottom - client_rect.top;
    //スクリーンサイズを取得して常に中心に配置されるように設定
    int x = GetSystemMetrics(SM_CXSCREEN) / 2 - client_rect.right / 2;
    int y = GetSystemMetrics(SM_CYSCREEN) / 2 - client_rect.bottom / 2;

    //ウィンドウの作成
    hWnd = CreateWindow(
      ClassName,              //_In_opt_ LPCWSTR lpClassName,   登録されているクラス名
      ClassName,              //_In_opt_ LPCWSTR lpWindowName,  ウィンドウ名
      WS_OVERLAPPEDWINDOW,    //_In_ DWORD dwStyle,             ウィンドウのスタイル
      x,                      //_In_ int X,                     ディスプレイのスタートＸ座標
      y,                      //_In_ int Y,                     ディスプレイのスタートＹ座標
      width,                  //_In_ int nWidth,                ウィンドウの横幅
      height,                 //_In_ int nHeight,               ウィンドウの縦幅
      NULL,                   //_In_opt_ HWND hWndParent,       作成されている親ウインドウのハンドル
      NULL,                   //_In_opt_ HMENU hMenu,           メニューバーのハンドル
      hInstance,              //_In_opt_ HINSTANCE hInstance,   ウィンドウに関連付けられるインスタンスハンドル
      NULL                    //_In_opt_ LPVOID lpParam         追加のアプリケーションデータ
    );
    if (!hWnd) return E_FAIL;

    is_init = true;
  }
  return S_OK;
}
//ウィンドウメッセージを処理する構造体
bool ProcessMessage()
{
  //ウィンドウプロシージャのメッセージを処理する
  if (PeekMessage(&Msg,     //_Out_ LPMSG lpMsg,        メッセージ情報ハンドル
                  NULL,     //_In_opt_ HWND hWnd,       ウィンドウのハンドル、NULLでデフォルトが呼ばれる
                  0,        //_In_ UINT wMsgFilterMin,  取得対象のメッセージの最小値を設定する
                  0,        //_In_ UINT wMsgFilterMax,  取得対象のメッセージの最大値を設定する
                  PM_REMOVE //_In_ UINT wRemoveMsg      削除オプション　PM_REMOVEでメッセージを削除する、PM_NOREMOVEで削除しない
  ))
  {
    //送られてきたキーボードメッセージの大小文字に分類する
    TranslateMessage(&Msg); //_In_ CONST MSG *lpMsg
    //メッセージをウィンドウズプロシージャに送る
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