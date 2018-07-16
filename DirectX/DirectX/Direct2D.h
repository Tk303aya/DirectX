#pragma once
#include "main.h"

namespace directx
{
//テクスチャを描画する
//IDirect3DVertexBuffer9 *buffer  テクスチャを貼り付ける２Dプレーンオブジェクト
//LPDIRECT3DTEXTURE9 *texture     テクスチャ情報
HRESULT Draw2D(LPDIRECT3DVERTEXBUFFER9 buffer, LPDIRECT3DTEXTURE9 texture);

HRESULT Load2D(LPDIRECT3DTEXTURE9 *texture, LPCWSTR pass);
}