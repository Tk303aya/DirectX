#pragma once
#include "main.h"
#include "DirectString.h"
#include "Direct2D.h"
#include "Direct3D.h"
#include "DirectShader.h"

namespace directx
{
/// 頂点関係 ///
//
//座標変換済み頂点情報　２D描画に必要
#define FVF_CONVERTED_CUSTOM ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 ) // 座標変換済み頂点
struct CustomVertexConverted
{
  float x, y, z;// 頂点座標 
  float rhw;    // 除算数
  DWORD dwColor;// 頂点の色 ARGB
  float u, v;   //　テクスチャ座標 
};
constexpr int k2dSize = sizeof(CustomVertexConverted);

//座標変換済みでない頂点情報
#define FVF_CUSTOM (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
struct CustomVertex
{
  float x, y, z;//頂点座標
  DWORD dwColor;//頂点の色 ARGB
  float u, v;   //テクスチャ座標
};
constexpr int k3dSize = sizeof(CustomVertex);

//初期化関数
HRESULT DirectInit();

//終了関数
void DirectRelease();

//描画開始関数
bool ScreenStart();

//描画終了関数
bool ScreenEnd();

//DirectDeviceの取得
const LPDIRECT3DDEVICE9 GetDirectDevice();
}