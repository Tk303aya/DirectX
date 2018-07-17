#pragma once
#include "main.h"

namespace directx
{

//カメラ情報の設定
//D3DXVECTOR3 cam_pos,      カメラ座標
//D3DXVECTOR3 cam_target,   カメラの注視点（見る方向）
//D3DXVECTOR3 cam_up,       カメラの上方向
//float cam_fovy_to_radian, カメラの角度（ラジアン角）
//float cam_near,           最近値（どこから描画するか）注：０はエラー
//float cam_far             最遠値（どこまで描画するか）
void SetCamera(D3DXVECTOR3 cam_pos, D3DXVECTOR3 cam_target, D3DXVECTOR3 cam_up,
               float cam_fovy_to_radian, float cam_near, float cam_far);

//Xファイルの読み込み
//LPCTSTR file_name,        Xファイルのあるアドレス
//LPD3DXBUFFER *materials,  取得するマテリアル情報
//DWORD &num_materials,     取得するマテリアル数
//LPD3DXMESH *mesh          取得するメッシュ情報
HRESULT Load3DModelToXFile(LPCTSTR file_name, LPD3DXBUFFER *materials, DWORD &num_materials, LPD3DXMESH *mesh);

//モデルの描画
HRESULT Draw3D(D3DVECTOR position, LPD3DXBUFFER materials, DWORD num_materials, LPD3DXMESH mesh);

//モデルの解放
void Release3D(LPD3DXBUFFER materials, LPD3DXMESH mesh);

}