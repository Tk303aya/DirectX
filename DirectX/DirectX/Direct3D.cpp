#include "Direct3D.h"

namespace directx
{
//�J�������
D3DXVECTOR3 cam_pos, cam_target, cam_up;
float cam_fovy, cam_near, cam_far;
void SetCamera(D3DXVECTOR3 cam_pos, D3DXVECTOR3 cam_target, D3DXVECTOR3 cam_up, 
               float cam_fovy_to_radian, float cam_near, float cam_far)
{
  directx::cam_pos    = cam_pos;
  directx::cam_target = cam_target;
  directx::cam_up     = cam_up;
  directx::cam_fovy   = cam_fovy_to_radian;
  if (cam_near <= 0) cam_near = 0.1f;
  directx::cam_near   = cam_near;
  directx::cam_far    = cam_far;
}

HRESULT Load3DModelToXFile(LPCTSTR file_name, LPD3DXBUFFER *materials, DWORD &num_materials, LPD3DXMESH *mesh)
{
  // X�t�@�C������I�u�W�F�N�g����
  ID3DXBuffer *pMaterials;
  DWORD NumMaterials;
  ID3DXMesh *pMesh;

  HRESULT hr;
  hr = D3DXLoadMeshFromX(
    file_name,          //LPCWSTR pFilename,                �t�@�C����
    D3DXMESH_MANAGED,   //DWORD Options,                    ���b�V���쐬���̃I�v�V�����@D3DXMESH�񋓌^�Q��
    GetDirectDevice(),  //LPDIRECT3DDEVICE9 pD3DDevice,     �g�p���Ă���f�o�C�X��
    NULL,               //LPD3DXBUFFER *ppAdjacency,        �אڂ��Ă��郁�b�V���̏���3�܂Ŏ擾�ł���
    &pMaterials,        //LPD3DXBUFFER *ppMaterials,        �}�e���A�����i�[�p�ϐ�
    NULL,               //LPD3DXBUFFER *ppEffectInstances,  ���b�V�����̑���1���Ƃ̃G�t�F�N�g�C���X�^���X�̔z����܂ރ|�C���^
                        //                                  ���F�����̃G�t�F�N�g�Ƃ̓����_�����O�̃J�X�^�}�C�Y�̂��Ƃł���
    &NumMaterials,      //DWORD *pNumMaterials,             �}�e���A�����̏��i�[�p�ϐ�
    &pMesh);            //LPD3DXMESH *ppMesh);              ���b�V�����i�[�p�ϐ�
  if (FAILED(hr)) return E_FAIL;
  *materials = pMaterials;
  num_materials = NumMaterials;
  *mesh = pMesh;

  return S_OK;
}

HRESULT Draw3D(D3DVECTOR position, LPD3DXBUFFER materials, DWORD num_materials, LPD3DXMESH mesh)
{
  D3DXMATRIX world, view, persp;
  
  //���[���h���W�̏�����
  D3DXMatrixIdentity(&world);

  //���W���烏�[���h���W�����߂�
  D3DXMatrixTranslation(&world, position.x, position.y, position.z);   

  // �r���[�ϊ�
  D3DXMatrixLookAtLH(&view, &cam_pos, &cam_target, &cam_up);

  // �ˉe�ϊ�
  int width, height;
  winapi::GetWindowSize(width, height);
  float aspect = width / static_cast<float>(height);
  D3DXMatrixPerspectiveFovLH(&persp, cam_fovy, aspect, cam_near, cam_far);

  //�ϊ��s��o�^
  GetDirectDevice()->SetTransform(D3DTS_WORLD, &world);
  GetDirectDevice()->SetTransform(D3DTS_VIEW, &view);
  GetDirectDevice()->SetTransform(D3DTS_PROJECTION, &persp);
  
  for (int i = 0; i<num_materials; i++)
  {
    D3DXMATERIAL *mtrl = (D3DXMATERIAL*)(materials->GetBufferPointer());
    GetDirectDevice()->SetMaterial(&mtrl->MatD3D);
    mesh->DrawSubset(i);
  };
  GetDirectDevice()->SetTransform(D3DTS_WORLD, &world);
  GetDirectDevice()->SetTransform(D3DTS_VIEW, &view);
  GetDirectDevice()->SetTransform(D3DTS_PROJECTION, &persp);

  return S_OK;
}

void Release3D(LPD3DXBUFFER materials, LPD3DXMESH mesh)
{
  materials->Release();
  mesh->Release();
}

}