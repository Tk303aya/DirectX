#pragma once
#include "main.h"

namespace directx
{
//テクスチャを描画する
//IDirect3DVertexBuffer9 *buffer  テクスチャを貼り付ける２Dプレーンオブジェクト
//LPDIRECT3DTEXTURE9 *texture     テクスチャ情報
HRESULT Draw2D(LPDIRECT3DVERTEXBUFFER9 buffer, LPDIRECT3DTEXTURE9 texture);


//画像の読み込み
//LPDIRECT3DTEXTURE9 *texture,  読み込むテクスチャ
//LPCWSTR pass                  画像のパス
HRESULT Load2D(LPDIRECT3DTEXTURE9 *texture, LPCTSTR pass);

//画像情報の削除
void Release2D(LPDIRECT3DVERTEXBUFFER9 buffer, LPDIRECT3DTEXTURE9 texture);
}