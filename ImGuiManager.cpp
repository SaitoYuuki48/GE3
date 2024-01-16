#include "ImGuiManager.h"

#include "Externals/imgui/imgui.h"
#include"Externals/imgui/imgui_impl_dx12.h"
#include "Externals/imgui/imgui_impl_win32.h"

void ImGuiManager::Initialize(HWND hwnd, DirectXCommon* dxCommon)
{
	//ImGui‰Šú‰»ˆ— //1:15:43
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX12_Init()

}
