#pragma once
#include "DirectXCommon.h"
#include <d3d12.h>
#include <wrl.h>

#include "SpriteCommon.h"

// スプライト
class Sprite
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	// 初期化
	void Initialize(DirectXCommon* dxCommon, SpriteCommon* common);

	//描画処理
	void Draw();

private:
	DirectXCommon* dxCommon_ = nullptr;
	SpriteCommon* common_ = nullptr;

	ComPtr<ID3D12Resource> vertexResource;
	//頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
};

