#pragma once
#include "main.h"

namespace directx
{
//�P�����e�N�X�`�����쐬����
//LPSTSRT put_char,               �e�N�X�`�����쐬����P�����i���p�S�p���Ȃ����P�����̂݁j
//int font_size,                  �t�H���g�T�C�Y
//float &get_width,               �擾�ł���e�N�X�`���̉���
//float &get_heigth,              �擾�ł���e�N�X�`���̏c��
//LPDIRECT3DTEXTURE9 get_texture  �擾�ł���e�N�X�`���\����
HRESULT CreateCharToTexture(LPCTSTR put_char, int font_size, float &get_width, float &get_height, LPDIRECT3DTEXTURE9 *get_texture);

//���W�ϊ��ς݂̂QD�v���[���I�u�W�F�N�g���쐬����
//float x,y                 �`��X�^�[�g���W�i����j
//float width,height        �傫��
//DWORD color,              �J���[�@������ARGB�̏�
//IDirect3DVertexBuffer9**  �i�[���钸�_�o�b�t�@�\����
HRESULT Create2DObject(float x, float y, float width, float height,DWORD color, LPDIRECT3DVERTEXBUFFER9 *get_buffer);

//�����̃f�o�b�O�o��
void AddDebugString(const char *FormatString, ...);
//�f�o�b�O�����̃N���A
void ClearDebugString();

//�f�o�b�O�����o�͗p�N���X
void PutDebugString();
}