#include "DirectX.h"

namespace directx
{
//DirectXのコンポーネント
LPDIRECT3D9 direct_9 = nullptr;
LPDIRECT3DDEVICE9 direct_9_device = nullptr;
ID3DXSprite *sprite = nullptr;

//初期化制御系
bool is_init = false;

HRESULT DirectInit()
{
  if (!is_init)
  {
    //Direct3Dの初期化
    direct_9 = Direct3DCreate9(D3D_SDK_VERSION);  //UINT SDKVersion   SDKのバージョンしてい 注：ただし正常にSDKバージョンを合わせるためにD3D_SDK_VERSIONを指定しなければならない
    if (!direct_9) return E_FAIL;

    int width, height;
    winapi::GetWindowSize(width, height);

    //DirectXのパラメータ設定
    D3DPRESENT_PARAMETERS d3dpp =
    {
      static_cast<UINT>(width),           //UINT                BackBufferWidth;              裏画面の横幅
      static_cast<UINT>(height),          //UINT                BackBufferHeight;             裏画面の縦幅
      D3DFMT_UNKNOWN,                     //D3DFORMAT           BackBufferFormat;             画面のフォーマット情報
      0,                                  //UINT                BackBufferCount;              バックバッファの枚数
                                          //                                                  
      D3DMULTISAMPLE_NONE,                //D3DMULTISAMPLE_TYPE MultiSampleType;              マルチサンプルの数を指定する
      0,                                  //DWORD               MultiSampleQuality;           マルチサンプルの品質レベル
                                          //                                                  
      D3DSWAPEFFECT_DISCARD,              //D3DSWAPEFFECT       SwapEffect;                   フロントバッファとバックバッファの切り替え方法
      NULL,                               //HWND                hDeviceWindow;                画面を描画するウィンドウハンドル
      TRUE,                               //BOOL                Windowed;                     スクリーンモードの定義　TRUE：ウィンドウモード　FALSE：スクリーンモード
      TRUE,                               //BOOL                EnableAutoDepthStencil;       震度ステンシルバッファの有無
      D3DFMT_D24S8,                       //D3DFORMAT           AutoDepthStencilFormat;       ステンシルバッファのフォーマットを指定
      D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL,//DWORD               Flags;                        バックバッファからフロントバッファに切り替える時の機能を指定する
                                          //                                                  
                                          ///* FullScreen_RefreshRateInHz must be zero for Windowed mode */
      D3DPRESENT_RATE_DEFAULT,            //UINT                FullScreen_RefreshRateInHz;   フルスクリーンでのリフレッシュレートの指定
      D3DPRESENT_INTERVAL_DEFAULT         //UINT                PresentationInterval;         スワップの書き換えタイミングの設定
    };

    //DirectXデバイスの作成
    //最大で
    //ハードウェア処理×ハードウェア頂点処理
    //ハードウェア処理×ソフトウェア頂点処理
    //ソフトウェア処理×ハードウェア頂点処理
    //ソフトウェア処理×ソフトウェア頂点処理
    //の４回行い作成する、これ以外はそもそもDirectX自体が使用できない可能性がある
    // CreateDevice(
    //THIS_ UINT Adapter,                             表示するディスプレイの番号 D3DADAPTER_DEFAULT でデフォルトのディスプレイに設定される
    //D3DDEVTYPE DeviceType,                          処理の方法をD3DDEVTYPE列挙型で指定、ハードウェア処理とソフトウェア処理が存在し、ハードウェアの方が軽い
    //HWND hFocusWindow,                              描画を行うウィンドウハンドル
    //DWORD BehaviorFlags,                            デバイスの作成を制御するオプション設定、少なくとも頂点処理をハードウェアかソフトウェアのどちらかで行うか指定が必要
    //D3DPRESENT_PARAMETERS* pPresentationParameters, DirectXのパラメータを渡す
    //IDirect3DDevice9** ppReturnedDeviceInterface);  受け取るデバイスの構造体
    if (FAILED(direct_9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, winapi::GetHwnd(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &direct_9_device)))
    if (FAILED(direct_9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, winapi::GetHwnd(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &direct_9_device)))
    {
      direct_9->Release();
      return E_FAIL;
    }
    is_init = true;
  }
  return S_OK;
}
void DirectRelease()
{
  if (direct_9) direct_9->Release();
  if (direct_9_device) direct_9_device->Release();
  if (sprite) sprite->Release();
}
bool ScreenStart()
{
  HRESULT hr;//失敗判定
  //裏画面の描画している情報を削除
  hr = direct_9_device->Clear(
    0,                                  //THIS_ DWORD Count,      下の矩形の数
    NULL,                               //CONST D3DRECT* pRects,  クリアする矩形範囲　NULLは全てクリアする
    D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, //DWORD Flags,            クリアするサーフェイスを示すフラグ　ステンシルバッファ、レンダリングターゲット、深度バッファがあり複数指定できる
    D3DCOLOR_XRGB(50,100,250),          //D3DCOLOR Color,         レンダリングターゲットをクリアするカラー
    1.0f,                               //float Z,                深度バッファをクリアする値
    0                                   //DWORD Stencil           ステンシルバッファをクリアする値
  );
  if (FAILED(hr)) return false;

  //裏画面描画開始関数
  hr = direct_9_device->BeginScene();
  if (FAILED(hr)) return false;

  return true;
}
bool ScreenEnd()
{
  HRESULT hr;//失敗判定

  //裏画面描画終了関数
  hr = direct_9_device->EndScene();
  if (FAILED(hr)) return false;

  //裏画面を表画面に出力 注：スワップ チェーンが D3DSWAPEFFECT_COPY で作成されていない限り全て NULL でなければならない
  hr = direct_9_device->Present(
    NULL, //THIS_ CONST RECT* pSourceRect,  切り替え領域
    NULL, //CONST RECT* pDestRect,          塗りつぶし領域
    NULL, //HWND hDestWindowOverride,       対象のウィンドウハンドル
    NULL  //CONST RGNDATA* pDirtyRegion     バックバッファ座標で表現される
  );
  if (FAILED(hr)) return false;

  return true;
}
const LPDIRECT3DDEVICE9 GetDirectDevice()
{
  return direct_9_device;
}
 ID3DXSprite* const GetID3DXSprite()
{
  return sprite;
}
}