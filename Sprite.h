#pragma once
#include "DirectXCommon.h"
#include <d3d12.h>
#include <wrl.h>

#include <DirectXMath.h>

#include "SpriteCommon.h"
#include "Matrix4x4.h"
#include "Vector3.h"

// スプライト
class Sprite
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	struct  Transform
	{
		Vector3 scale;
		Vector3 rotate;
		Vector3 translate;
	};
public:
	// 初期化
	void Initialize(DirectXCommon* dxCommon, SpriteCommon* common);

	//描画処理
	void Draw();

private:
	//頂点情報作成
	void CreateVertex();
	//マテリアル作成
	void CreateMaterial();
	//行列情報作成
	void CreateWVP();

private:
	DirectXCommon* dxCommon_ = nullptr;
	SpriteCommon* common_ = nullptr;

	ComPtr<ID3D12Resource> vertexResource;
	//頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	//マテリアル情報
	ComPtr<ID3D12Resource> materialResource;

	//行列情報
	ComPtr<ID3D12Resource> wvpResource;
	Matrix4x4* wvpData = nullptr;

	//パラメータ
	DirectX::XMFLOAT4 color_ = { 1.0f,0.0f,0.0f,1.0f };
	Transform transform = { {1,1,1},{0,0,0},{0,0,0} }; // Scale Rotate Translate

	//カメラ
	Transform cameraTransform = { {1,1,1},{0,0,0},{0,0,-5} };
};

