#pragma once
#include "main.h"

namespace directx
{
//�e�N�X�`����`�悷��
//IDirect3DVertexBuffer9 *buffer  �e�N�X�`����\��t����QD�v���[���I�u�W�F�N�g
//LPDIRECT3DTEXTURE9 *texture     �e�N�X�`�����
HRESULT Draw2D(LPDIRECT3DVERTEXBUFFER9 buffer, LPDIRECT3DTEXTURE9 texture);


//�摜�̓ǂݍ���
//LPDIRECT3DTEXTURE9 *texture,  �ǂݍ��ރe�N�X�`��
//LPCWSTR pass                  �摜�̃p�X
HRESULT Load2D(LPDIRECT3DTEXTURE9 *texture, LPCTSTR pass);

//�摜���̍폜
void Release2D(LPDIRECT3DVERTEXBUFFER9 buffer, LPDIRECT3DTEXTURE9 texture);
}