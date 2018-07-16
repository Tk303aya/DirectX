#pragma once
#include "main.h"

namespace winapi
{
//���C�����[�v�֐��|�C���^
typedef bool(*MainLoopFunc)();

//WindowsAPI�̏������ϐ�
HRESULT WinApiInit(HINSTANCE hInstance);

//���C�����[�v����
void MainLoop(MainLoopFunc main_loop_func);

//�E�B���h�E�̕��擾
void GetWindowSize(int &width, int &height);

//�V�X�e���I���̊֐��@���F���C���֐��̃��^�[���ŕԂ��l���߂�l�Ƃ��ďo�͂����
int SystemReturn();

const HWND GetHwnd();
}
