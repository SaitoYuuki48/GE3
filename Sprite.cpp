#include "Sprite.h"

#include <DirectXMath.h>

#include "BufferResource.h"
#include "gMath.h"

using namespace Microsoft::WRL;
using namespace DirectX;

void Sprite::Initialize(DirectXCommon* dxCommon, SpriteCommon* common)
{
	dxCommon_ = dxCommon;
	common_ = common;

	//頂点情報
	CreateVertex();
	//色
	CreateMaterial();
	//行列
	CreateWVP();
}

void Sprite::Draw()
{
	//Y軸中心に回転
	transform.rotate.y += 0.03f;
	//ワールド
	//行列変換
	Matrix4x4 worldMatrix = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);

	//カメラ
	Matrix4x4 cameraMatrix = MakeAffineMatrix(cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);
	//View
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	//Projection
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, (float)WinApp::window_width / (float)WinApp::window_height, 0.1f, 100.0f);
	//WVP
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	//行列の代入
	*wvpData = worldViewProjectionMatrix;

	dxCommon_->GetCommandList()->SetGraphicsRootSignature(common_->GetRootSignature());
	dxCommon_->GetCommandList()->SetPipelineState(common_->GetPipelineState());

	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	//形状を設定。
	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// 描画
	//色
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	//行列
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());

	dxCommon_->GetCommandList()->DrawInstanced(3, 1, 0, 0);
}

void Sprite::CreateVertex()
{
	//VertexResourceを生成する
	vertexResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(XMFLOAT4) * 3);

	//リソースの先頭のアドレスから使う
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	//使用するリソースのサイズ
	vertexBufferView.SizeInBytes = sizeof(XMFLOAT4) * 3;
	//1頂点あたりのサイズ
	vertexBufferView.StrideInBytes = sizeof(XMFLOAT4);

	//頂点リソースにデータを書き込む
	XMFLOAT4* vertexData = nullptr;
	//書き込むためのアドレスを取得
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	//左下
	vertexData[0] = { -0.5f,-0.5f,0.0f,1.0f };
	//上
	vertexData[1] = { 0.0f,0.5f,0.0f,1.0f };
	//右下
	vertexData[2] = { 0.5f,-0.5f,0.0f,1.0f };
}

void Sprite::CreateMaterial()
{
	materialResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(XMFLOAT4));

	XMFLOAT4* materialData = nullptr;
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));

	*materialData = color_;
}

void Sprite::CreateWVP()
{
	wvpResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(XMMATRIX));

	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));

	*wvpData = MakeIdentity4x4();
}
