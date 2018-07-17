#include "main.h"
#include "DirectX.h"

LPDIRECT3DTEXTURE9 tex;
LPDIRECT3DVERTEXBUFFER9 vertex;
LPDIRECT3DTEXTURE9 ch;
LPDIRECT3DVERTEXBUFFER9 chv;
struct Object
{
  LPD3DXBUFFER materials;
  DWORD num_materials;
  LPD3DXMESH mesh;
};
Object ball;
Object box;
Object plate;

float cam_direction = 80;

bool MainLoopFunc()
{
  //カメラ設定
  static float i = 0;
  directx::SetCamera(D3DXVECTOR3(sin(i)*cam_direction, cam_direction/2, cos(i)*cam_direction), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0),
                     D3DXToRadian(45), 0.1f, 10000);
  i+=0.01f;

  directx::Draw3D(D3DXVECTOR3(10, 10, 0), ball.materials, ball.num_materials, ball.mesh);
  directx::Draw3D(D3DXVECTOR3(0, 10, 0), box.materials, box.num_materials, box.mesh);
  directx::Draw3D(D3DXVECTOR3(0, 0, 0), plate.materials, plate.num_materials, plate.mesh);
  directx::Draw2D(vertex, tex);
  directx::Draw2D(chv, ch);
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
  float w, h;
  //文字読み込み
  directx::CreateCharToTexture(_T("あ"), 100, w, h, &ch);
  directx::Create2DObject(0, 0, w, h, 0xf0ff0000, &chv);
  //画像読み込み
  directx::Load2D(&tex, _T("test.png"));
  directx::Create2DObject(0, 0, 300, 100, 0x80ffffff, &vertex);
  //モデル読み込み
  directx::Load3DModelToXFile(_T("sphere.x"), &ball.materials, ball.num_materials, &ball.mesh);
  directx::Load3DModelToXFile(_T("Cube2.x"),  &box.materials, box.num_materials, &box.mesh);
  directx::Load3DModelToXFile(_T("Plate.x"),  &plate.materials, plate.num_materials, &plate.mesh);
    
  //ライト設定
  // ライト
  D3DLIGHT9 light;
  ZeroMemory(&light, sizeof(D3DLIGHT9));
  light.Direction = D3DXVECTOR3(1, -1, 1);
  light.Type = D3DLIGHT_DIRECTIONAL;
  light.Diffuse   = {0.7f, 0.7f, 0.7f, 1.0f};
  directx::GetDirectDevice()->SetLight(0, &light);
  directx::GetDirectDevice()->LightEnable(0, TRUE);     // ライトを照らす

  //メインループ関数
  winapi::MainLoop(MainLoopFunc);

  //開放関数
  directx::Release3D(ball.materials, ball.mesh);
  directx::Release3D(box.materials, box.mesh);
  directx::Release3D(plate.materials, plate.mesh);
  directx::Release2D(vertex, tex);
  directx::Release2D(chv, ch);
  
  //DirectXの開放
  directx::DirectRelease();

  //通常終了
  return winapi::SystemReturn();
}