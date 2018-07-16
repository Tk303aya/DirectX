#pragma once
#include "main.h"

namespace directx
{
//１文字テクスチャを作成する
//LPSTSRT put_char,               テクスチャを作成する１文字（半角全角問わないが１文字のみ）
//int font_size,                  フォントサイズ
//float &get_width,               取得できるテクスチャの横幅
//float &get_heigth,              取得できるテクスチャの縦幅
//LPDIRECT3DTEXTURE9 get_texture  取得できるテクスチャ構造体
HRESULT CreateCharToTexture(LPCTSTR put_char, int font_size, float &get_width, float &get_height, LPDIRECT3DTEXTURE9 *get_texture);

//座標変換済みの２Dプレーンオブジェクトを作成する
//float x,y                 描画スタート座標（左上）
//float width,height        大きさ
//DWORD color,              カラー　左からARGBの順
//IDirect3DVertexBuffer9**  格納する頂点バッファ構造体
HRESULT Create2DObject(float x, float y, float width, float height,DWORD color, LPDIRECT3DVERTEXBUFFER9 *get_buffer);

//文字のデバッグ出力
void AddDebugString(const char *FormatString, ...);
//デバッグ文字のクリア
void ClearDebugString();

//デバッグ文字出力用クラス
void PutDebugString();
}