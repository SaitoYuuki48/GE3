#pragma once
#include <Windows.h>

class WinApp
{
public: // �����o�֐�
	// �E�B���h�E�v���V�[�W��
	LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	// ������
	void Initialize();
	// �X�V
	void Update();
};

