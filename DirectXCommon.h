#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_6.h>

#include <vector>

#include "WinApp.h"

class DirectXCommon
{
private:
	//namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数
	// 初期化
	void Initialize(WinApp* winApp);

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
};