#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_6.h>

#include <vector>
#include <chrono>

#include "WinApp.h"

class DirectXCommon
{
private:
	//namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数
	// 初期化
	void Initialize(WinApp* winApp);

	//描画前処理
	void PreDraw();
	//描画後処理
	void PostDraw();

	//Getter
	ID3D12Device* GetDevice() const { return device.Get(); }
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }

private:
	//デバイス
	void DeviceInitialize();
	//コマンド
	void CommandInitialize();
	//スワップチェーン
	void SwapChainInitialize();
	//レンダーターゲット
	void RenderTargetInitialize();
	//深度バッファ
	void DepthBufferInitialize();
	//フェンス
	void FenceInitialize();

	//ディスクリプタヒープ
	ID3D12DescriptorHeap* CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);


	//FPS固定初期化処理
	void InitializeFixFPS();
	//FPS固定更新処理
	void UpdataFixFPS();

private:
	WinApp* winApp_ = nullptr;

	//デバイス
	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory7> dxgiFactory;
	//コマンド
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;
	//スワップチェーン
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	ComPtr<IDXGISwapChain4> swapChain;
	//レンダーターゲット
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	// バックバッファ
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	//深度バッファ
	ComPtr<ID3D12Resource> depthBuff;
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	//フェンス
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
	//描画前処理
	D3D12_RESOURCE_BARRIER barrierDesc{};

	//記録用時間計測の変数
	std::chrono::steady_clock::time_point reference_;

	//ディスクリプタヒープ
	//RTV (ゲーム画面を保存しておく)
	ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
	//SRV (画像などを保存しておくもの)
	ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap;
};