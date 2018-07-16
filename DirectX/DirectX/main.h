#pragma once
//デバッグモードで起動
#define DEBUG_MODE true

#ifndef UNICODE
#define UNICODE
#endif // !UNICODE


//ライブラリリンク設定
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//インクルードファイル
#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <math.h>

//コンソール出力
#if DEBUG_MODE
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif

#include "WindowAPI.h"
#include "DirectX.h"