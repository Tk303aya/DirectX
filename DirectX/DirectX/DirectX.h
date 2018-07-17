#pragma once
#include "main.h"
#include "DirectString.h"
#include "Direct2D.h"
#include "Direct3D.h"
#include "DirectShader.h"

namespace directx
{
/// ���_�֌W ///
//
//���W�ϊ��ςݒ��_���@�QD�`��ɕK�v
#define FVF_CONVERTED_CUSTOM ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 ) // ���W�ϊ��ςݒ��_
struct CustomVertexConverted
{
  float x, y, z;// ���_���W 
  float rhw;    // ���Z��
  DWORD dwColor;// ���_�̐F ARGB
  float u, v;   //�@�e�N�X�`�����W 
};
constexpr int k2dSize = sizeof(CustomVertexConverted);

//���W�ϊ��ς݂łȂ����_���
#define FVF_CUSTOM (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
struct CustomVertex
{
  float x, y, z;//���_���W
  DWORD dwColor;//���_�̐F ARGB
  float u, v;   //�e�N�X�`�����W
};
constexpr int k3dSize = sizeof(CustomVertex);

//�������֐�
HRESULT DirectInit();

//�I���֐�
void DirectRelease();

//�`��J�n�֐�
bool ScreenStart();

//�`��I���֐�
bool ScreenEnd();

//DirectDevice�̎擾
const LPDIRECT3DDEVICE9 GetDirectDevice();
}