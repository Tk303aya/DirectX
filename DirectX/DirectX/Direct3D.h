#pragma once
#include "main.h"

namespace directx
{

//�J�������̐ݒ�
//D3DXVECTOR3 cam_pos,      �J�������W
//D3DXVECTOR3 cam_target,   �J�����̒����_�i��������j
//D3DXVECTOR3 cam_up,       �J�����̏����
//float cam_fovy_to_radian, �J�����̊p�x�i���W�A���p�j
//float cam_near,           �ŋߒl�i�ǂ�����`�悷�邩�j���F�O�̓G���[
//float cam_far             �ŉ��l�i�ǂ��܂ŕ`�悷�邩�j
void SetCamera(D3DXVECTOR3 cam_pos, D3DXVECTOR3 cam_target, D3DXVECTOR3 cam_up,
               float cam_fovy_to_radian, float cam_near, float cam_far);

//X�t�@�C���̓ǂݍ���
//LPCTSTR file_name,        X�t�@�C���̂���A�h���X
//LPD3DXBUFFER *materials,  �擾����}�e���A�����
//DWORD &num_materials,     �擾����}�e���A����
//LPD3DXMESH *mesh          �擾���郁�b�V�����
HRESULT Load3DModelToXFile(LPCTSTR file_name, LPD3DXBUFFER *materials, DWORD &num_materials, LPD3DXMESH *mesh);

//���f���̕`��
HRESULT Draw3D(D3DVECTOR position, LPD3DXBUFFER materials, DWORD num_materials, LPD3DXMESH mesh);

//���f���̉��
void Release3D(LPD3DXBUFFER materials, LPD3DXMESH mesh);

}