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
  //�J�����ݒ�
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
  float w, h;
  //�����ǂݍ���
  directx::CreateCharToTexture(_T("��"), 100, w, h, &ch);
  directx::Create2DObject(0, 0, w, h, 0xf0ff0000, &chv);
  //�摜�ǂݍ���
  directx::Load2D(&tex, _T("test.png"));
  directx::Create2DObject(0, 0, 300, 100, 0x80ffffff, &vertex);
  //���f���ǂݍ���
  directx::Load3DModelToXFile(_T("sphere.x"), &ball.materials, ball.num_materials, &ball.mesh);
  directx::Load3DModelToXFile(_T("Cube2.x"),  &box.materials, box.num_materials, &box.mesh);
  directx::Load3DModelToXFile(_T("Plate.x"),  &plate.materials, plate.num_materials, &plate.mesh);
    
  //���C�g�ݒ�
  // ���C�g
  D3DLIGHT9 light;
  ZeroMemory(&light, sizeof(D3DLIGHT9));
  light.Direction = D3DXVECTOR3(1, -1, 1);
  light.Type = D3DLIGHT_DIRECTIONAL;
  light.Diffuse   = {0.7f, 0.7f, 0.7f, 1.0f};
  directx::GetDirectDevice()->SetLight(0, &light);
  directx::GetDirectDevice()->LightEnable(0, TRUE);     // ���C�g���Ƃ炷

  //���C�����[�v�֐�
  winapi::MainLoop(MainLoopFunc);

  //�J���֐�
  directx::Release3D(ball.materials, ball.mesh);
  directx::Release3D(box.materials, box.mesh);
  directx::Release3D(plate.materials, plate.mesh);
  directx::Release2D(vertex, tex);
  directx::Release2D(chv, ch);
  
  //DirectX�̊J��
  directx::DirectRelease();

  //�ʏ�I��
  return winapi::SystemReturn();
}