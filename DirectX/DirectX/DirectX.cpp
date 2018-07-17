#include "DirectX.h"

namespace directx
{
//DirectX�̃R���|�[�l���g
LPDIRECT3D9 direct_9 = nullptr;
LPDIRECT3DDEVICE9 direct_9_device = nullptr;
ID3DXSprite *sprite = nullptr;

//����������n
bool is_init = false;

HRESULT DirectInit()
{
  if (!is_init)
  {
    //Direct3D�̏�����
    direct_9 = Direct3DCreate9(D3D_SDK_VERSION);  //UINT SDKVersion   SDK�̃o�[�W�������Ă� ���F�����������SDK�o�[�W���������킹�邽�߂�D3D_SDK_VERSION���w�肵�Ȃ���΂Ȃ�Ȃ�
    if (!direct_9) return E_FAIL;

    int width, height;
    winapi::GetWindowSize(width, height);

    //DirectX�̃p�����[�^�ݒ�
    D3DPRESENT_PARAMETERS d3dpp =
    {
      static_cast<UINT>(width),           //UINT                BackBufferWidth;              ����ʂ̉���
      static_cast<UINT>(height),          //UINT                BackBufferHeight;             ����ʂ̏c��
      D3DFMT_UNKNOWN,                     //D3DFORMAT           BackBufferFormat;             ��ʂ̃t�H�[�}�b�g���
      0,                                  //UINT                BackBufferCount;              �o�b�N�o�b�t�@�̖���
                                          //                                                  
      D3DMULTISAMPLE_NONE,                //D3DMULTISAMPLE_TYPE MultiSampleType;              �}���`�T���v���̐����w�肷��
      0,                                  //DWORD               MultiSampleQuality;           �}���`�T���v���̕i�����x��
                                          //                                                  
      D3DSWAPEFFECT_DISCARD,              //D3DSWAPEFFECT       SwapEffect;                   �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̐؂�ւ����@
      NULL,                               //HWND                hDeviceWindow;                ��ʂ�`�悷��E�B���h�E�n���h��
      TRUE,                               //BOOL                Windowed;                     �X�N���[�����[�h�̒�`�@TRUE�F�E�B���h�E���[�h�@FALSE�F�X�N���[�����[�h
      TRUE,                               //BOOL                EnableAutoDepthStencil;       �k�x�X�e���V���o�b�t�@�̗L��
      D3DFMT_D24S8,                       //D3DFORMAT           AutoDepthStencilFormat;       �X�e���V���o�b�t�@�̃t�H�[�}�b�g���w��
      D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL,//DWORD               Flags;                        �o�b�N�o�b�t�@����t�����g�o�b�t�@�ɐ؂�ւ��鎞�̋@�\���w�肷��
                                          //                                                  
                                          ///* FullScreen_RefreshRateInHz must be zero for Windowed mode */
      D3DPRESENT_RATE_DEFAULT,            //UINT                FullScreen_RefreshRateInHz;   �t���X�N���[���ł̃��t���b�V�����[�g�̎w��
      D3DPRESENT_INTERVAL_DEFAULT         //UINT                PresentationInterval;         �X���b�v�̏��������^�C�~���O�̐ݒ�
    };

    //DirectX�f�o�C�X�̍쐬
    //�ő��
    //�n�[�h�E�F�A�����~�n�[�h�E�F�A���_����
    //�n�[�h�E�F�A�����~�\�t�g�E�F�A���_����
    //�\�t�g�E�F�A�����~�n�[�h�E�F�A���_����
    //�\�t�g�E�F�A�����~�\�t�g�E�F�A���_����
    //�̂S��s���쐬����A����ȊO�͂�������DirectX���̂��g�p�ł��Ȃ��\��������
    // CreateDevice(
    //THIS_ UINT Adapter,                             �\������f�B�X�v���C�̔ԍ� D3DADAPTER_DEFAULT �Ńf�t�H���g�̃f�B�X�v���C�ɐݒ肳���
    //D3DDEVTYPE DeviceType,                          �����̕��@��D3DDEVTYPE�񋓌^�Ŏw��A�n�[�h�E�F�A�����ƃ\�t�g�E�F�A���������݂��A�n�[�h�E�F�A�̕����y��
    //HWND hFocusWindow,                              �`����s���E�B���h�E�n���h��
    //DWORD BehaviorFlags,                            �f�o�C�X�̍쐬�𐧌䂷��I�v�V�����ݒ�A���Ȃ��Ƃ����_�������n�[�h�E�F�A���\�t�g�E�F�A�̂ǂ��炩�ōs�����w�肪�K�v
    //D3DPRESENT_PARAMETERS* pPresentationParameters, DirectX�̃p�����[�^��n��
    //IDirect3DDevice9** ppReturnedDeviceInterface);  �󂯎��f�o�C�X�̍\����
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
  HRESULT hr;//���s����
  //����ʂ̕`�悵�Ă�������폜
  hr = direct_9_device->Clear(
    0,                                  //THIS_ DWORD Count,      ���̋�`�̐�
    NULL,                               //CONST D3DRECT* pRects,  �N���A�����`�͈́@NULL�͑S�ăN���A����
    D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, //DWORD Flags,            �N���A����T�[�t�F�C�X�������t���O�@�X�e���V���o�b�t�@�A�����_�����O�^�[�Q�b�g�A�[�x�o�b�t�@�����蕡���w��ł���
    D3DCOLOR_XRGB(50,100,250),          //D3DCOLOR Color,         �����_�����O�^�[�Q�b�g���N���A����J���[
    1.0f,                               //float Z,                �[�x�o�b�t�@���N���A����l
    0                                   //DWORD Stencil           �X�e���V���o�b�t�@���N���A����l
  );
  if (FAILED(hr)) return false;

  //����ʕ`��J�n�֐�
  hr = direct_9_device->BeginScene();
  if (FAILED(hr)) return false;

  return true;
}
bool ScreenEnd()
{
  HRESULT hr;//���s����

  //����ʕ`��I���֐�
  hr = direct_9_device->EndScene();
  if (FAILED(hr)) return false;

  //����ʂ�\��ʂɏo�� ���F�X���b�v �`�F�[���� D3DSWAPEFFECT_COPY �ō쐬����Ă��Ȃ�����S�� NULL �łȂ���΂Ȃ�Ȃ�
  hr = direct_9_device->Present(
    NULL, //THIS_ CONST RECT* pSourceRect,  �؂�ւ��̈�
    NULL, //CONST RECT* pDestRect,          �h��Ԃ��̈�
    NULL, //HWND hDestWindowOverride,       �Ώۂ̃E�B���h�E�n���h��
    NULL  //CONST RGNDATA* pDirtyRegion     �o�b�N�o�b�t�@���W�ŕ\�������
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