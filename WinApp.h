#pragma once
#include <Windows.h>

class WinApp
{
public: //�ÓI�����o�֐�
	// �E�B���h�E�v���V�[�W��
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // �����o�֐�
	// ������
	void Initialize();
	// �X�V
	void Update();
};