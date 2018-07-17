#include "Direct3D.h"

namespace directx
{
//カメラ情報
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
  // Xファイルからオブジェクト生成
  ID3DXBuffer *pMaterials;
  DWORD NumMaterials;
  ID3DXMesh *pMesh;

  HRESULT hr;
  hr = D3DXLoadMeshFromX(
    file_name,          //LPCWSTR pFilename,                ファイル名
    D3DXMESH_MANAGED,   //DWORD Options,                    メッシュ作成時のオプション　D3DXMESH列挙型参照
    GetDirectDevice(),  //LPDIRECT3DDEVICE9 pD3DDevice,     使用しているデバイス名
    NULL,               //LPD3DXBUFFER *ppAdjacency,        隣接しているメッシュの情報を3つまで取得できる
    &pMaterials,        //LPD3DXBUFFER *ppMaterials,        マテリアル情報格納用変数
    NULL,               //LPD3DXBUFFER *ppEffectInstances,  メッシュ内の属性1つごとのエフェクトインスタンスの配列を含むポインタ
                        //                                  注：ここのエフェクトとはレンダリングのカスタマイズのことである
    &NumMaterials,      //DWORD *pNumMaterials,             マテリアル数の情報格納用変数
    &pMesh);            //LPD3DXMESH *ppMesh);              メッシュ情報格納用変数
  if (FAILED(hr)) return E_FAIL;
  *materials = pMaterials;
  num_materials = NumMaterials;
  *mesh = pMesh;

  return S_OK;
}

HRESULT Draw3D(D3DVECTOR position, LPD3DXBUFFER materials, DWORD num_materials, LPD3DXMESH mesh)
{
  D3DXMATRIX world, view, persp;
  
  //ワールド座標の初期化
  D3DXMatrixIdentity(&world);

  //座標からワールド座標を求める
  D3DXMatrixTranslation(&world, position.x, position.y, position.z);   

  // ビュー変換
  D3DXMatrixLookAtLH(&view, &cam_pos, &cam_target, &cam_up);

  // 射影変換
  int width, height;
  winapi::GetWindowSize(width, height);
  float aspect = width / static_cast<float>(height);
  D3DXMatrixPerspectiveFovLH(&persp, cam_fovy, aspect, cam_near, cam_far);

  //変換行列登録
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