#include "Direct2D.h"

namespace directx
{
HRESULT Draw2D(LPDIRECT3DVERTEXBUFFER9 buffer, LPDIRECT3DTEXTURE9 texture)
{
  //２D描画
  HRESULT hr;
  //テクスチャをポリゴンに書き込む方法を設定
  //SetTexture　
  //    第一：ポリゴンに書き込むテクスチャのステージ番号、最大８つ登録できる
  //    第二：設定するテクスチャ
  hr = GetDirectDevice()->SetTexture(0, texture);
  if (FAILED(hr)) return E_FAIL;
  //ポリゴンに書き込む際の計算方法の設定
  //SetTextureStageState
  //    第一：計算式を指定するテクスチャステージ番号
  //    第二：設定するテクスチャステート　D3DTEXTURESTAGESTATETYPE列挙型参照
  //    第三：第二引数によって指定する値が異なる
  
  //D3DTSS_COLORARG1  色の引数１（テクスチャ側）
  hr = GetDirectDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
  if (FAILED(hr)) return E_FAIL;
  //D3DTSS_COLOROP    色の演算子 
  hr = GetDirectDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
  if (FAILED(hr)) return E_FAIL;
  //D3DTSS_COLORARG2  色の引数２（ポリゴン側）
  hr = GetDirectDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
  if (FAILED(hr)) return E_FAIL;
  //D3DTSS_ALPHAARG1  アルファの引数１（テクスチャ側）
  hr = GetDirectDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
  if (FAILED(hr)) return E_FAIL;
  //D3DTSS_ALPHAOP    アルファの演算子
  hr = GetDirectDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
  if (FAILED(hr)) return E_FAIL;
  //D3DTSS_ALPHAARG2  アルファの引数２（ポリゴン側）
  hr = GetDirectDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE); // 板ポリのα値を利用
  if (FAILED(hr)) return E_FAIL;
  
  // レンダリングステート
  //SetRenderState 
  //  第一：変更対象のデバイスステート変数　D3DRENDERSTATETYPE列挙型参照
  //  第二：デバイスのレンダリングステートに設定する新しい値、第一によって意味が異なる
  hr = GetDirectDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
  if (FAILED(hr)) return E_FAIL;
  hr = GetDirectDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
  if (FAILED(hr)) return E_FAIL;
  hr = GetDirectDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
  if (FAILED(hr)) return E_FAIL;

  // 描画
  //ポリゴンを描画ストリームに登録
  hr = GetDirectDevice()->SetStreamSource(0, buffer, 0, k2dSize);
  if (FAILED(hr))return E_FAIL;
  //頂点形式を設定
  hr = GetDirectDevice()->SetFVF(FVF_CONVERTED_CUSTOM);
  if (FAILED(hr))return E_FAIL;
  //描画開始
  hr = GetDirectDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
  if (FAILED(hr))return E_FAIL;

  return S_OK;
}

HRESULT Load2D(LPDIRECT3DTEXTURE9 *texture, LPCWSTR pass)
{
  //成功判定用
  HRESULT hr;

  LPDIRECT3DTEXTURE9 tex;
  hr = D3DXCreateTextureFromFile(
    GetDirectDevice(),//LPDIRECT3DDEVICE9         pDevice,
    pass,             //LPCWSTR                   pSrcFile,
    &tex              //LPDIRECT3DTEXTURE9*       ppTexture
  );
  if (FAILED(hr)) return E_FAIL;
  *texture = tex;
  return S_OK;
}
}