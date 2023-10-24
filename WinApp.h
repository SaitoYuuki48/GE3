#pragma once
#include <Windows.h>

class WinApp
{
public: // メンバ関数
	// ウィンドウプロシージャ
	LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	// 初期化
	void Initialize();
	// 更新
	void Update();
};

