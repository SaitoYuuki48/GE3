﻿#pragma once
#include <Windows.h>

#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定
#include <dinput.h>
#include <wrl.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class Input
{
public: //メンバ関数
	//初期化
	void Initialize(HINSTANCE hInstance,HWND hwnd);

	//更新
	void Update();

public:
	//namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private: //メンバ変数
	// キーボードのデバイス
	ComPtr<IDirectInputDevice8> keyboard;
	//Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard;
};

