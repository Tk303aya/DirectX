#pragma once
#include "main.h"

namespace directx
{
//�e�N�X�`����`�悷��
//IDirect3DVertexBuffer9 *buffer  �e�N�X�`����\��t����QD�v���[���I�u�W�F�N�g
//LPDIRECT3DTEXTURE9 *texture     �e�N�X�`�����
HRESULT Draw2D(LPDIRECT3DVERTEXBUFFER9 buffer, LPDIRECT3DTEXTURE9 texture);

HRESULT Load2D(LPDIRECT3DTEXTURE9 *texture, LPCWSTR pass);
}