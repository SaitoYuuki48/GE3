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

	//���_���
	CreateVertex();
	//�F
	CreateMaterial();
	//�s��
	CreateWVP();
}

void Sprite::Draw()
{
	//Y�����S�ɉ�]
	transform.rotate.y += 0.03f;
	//���[���h
	//�s��ϊ�
	Matrix4x4 worldMatrix = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);

	//�J����
	Matrix4x4 cameraMatrix = MakeAffineMatrix(cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);
	//View
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	//Projection
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, (float)WinApp::window_width / (float)WinApp::window_height, 0.1f, 100.0f);
	//WVP
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	//�s��̑��
	*wvpData = worldViewProjectionMatrix;

	dxCommon_->GetCommandList()->SetGraphicsRootSignature(common_->GetRootSignature());
	dxCommon_->GetCommandList()->SetPipelineState(common_->GetPipelineState());

	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	//�`���ݒ�B
	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// �`��
	//�F
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	//�s��
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());

	dxCommon_->GetCommandList()->DrawInstanced(3, 1, 0, 0);
}

void Sprite::CreateVertex()
{
	//VertexResource�𐶐�����
	vertexResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(XMFLOAT4) * 3);

	//���\�[�X�̐擪�̃A�h���X����g��
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	//�g�p���郊�\�[�X�̃T�C�Y
	vertexBufferView.SizeInBytes = sizeof(XMFLOAT4) * 3;
	//1���_������̃T�C�Y
	vertexBufferView.StrideInBytes = sizeof(XMFLOAT4);

	//���_���\�[�X�Ƀf�[�^����������
	XMFLOAT4* vertexData = nullptr;
	//�������ނ��߂̃A�h���X���擾
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	//����
	vertexData[0] = { -0.5f,-0.5f,0.0f,1.0f };
	//��
	vertexData[1] = { 0.0f,0.5f,0.0f,1.0f };
	//�E��
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
