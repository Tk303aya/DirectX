#pragma once
//�f�o�b�O���[�h�ŋN��
#define DEBUG_MODE true

#ifndef UNICODE
#define UNICODE
#endif // !UNICODE


//���C�u���������N�ݒ�
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//�C���N���[�h�t�@�C��
#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <math.h>

//�R���\�[���o��
#if DEBUG_MODE
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif

#include "WindowAPI.h"
#include "DirectX.h"