/* =====================================================================
//! @param		�uFigure�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/08/20
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Figure.h"
#include <D3DX11.h>
#include "Constant.h"
#include "DXTKManager.h"
#include "Shader.h"

// ���O���
using namespace GucchiShader;

/* =====================================================================
//! ���@�e		�����������i�f�[�^�j
//! ���@��		�Ȃ�
//! �߂�l		�֐��̎��s���ʁiHRESULT�j
===================================================================== */
HRESULT Figure::Init3D()
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Shader& shader = Shader::GetInstance();

	// �V�F�[�_�t�@�C���ǂݍ���
	ID3DBlob* compiledShader = nullptr;
	//D3D11_BLEND_DESC bd;

	// �o�[�e�b�N�X�V�F�[�_�̍쐬
	if (FAILED(shader.MakeShader(SHADER_FILE_NAME_POINT, "VS", "vs_5_0", (void**)&m_pVShader, &compiledShader)))
	{
		return E_FAIL;
	}

	// ���_�̃C���v�b�g���C�A�E�g���`
	D3D11_INPUT_ELEMENT_DESC layout[] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,	D3D11_INPUT_PER_VERTEX_DATA, 0 };
	UINT elements = sizeof(layout) / sizeof(layout[0]);

	// ���_�̃C���v�b�g���C�A�E�g���쐬
	if (FAILED(dxtk.m_device->CreateInputLayout(layout, elements, compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), &shader.m_pInputLayout)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(compiledShader);

	// �s�N�Z���V�F�[�_�̍쐬
	if (FAILED(shader.MakeShader(SHADER_FILE_NAME_POINT, "PS", "ps_5_0", (void**)&m_pPShader, &compiledShader)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(compiledShader);

	// �s��̎󂯓n��
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(Shader::CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	// �R���X�^���g�o�b�t�@�̍쐬
	if (FAILED(dxtk.m_device->CreateBuffer(&cb, nullptr, &shader.m_pConstantBuffer)))
	{
		return E_FAIL;
	}

	// ����I��
	return S_OK;
}

/* =====================================================================
//! ���@�e		�����������i�f�[�^�j
//! ���@��		�Ȃ�
//! �߂�l		�֐��̎��s���ʁiHRESULT�j
===================================================================== */
HRESULT Figure::InitShader()
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Shader& shader = Shader::GetInstance();

	// �V�F�[�_�t�@�C���ǂݍ���
	ID3DBlob* compiledShader = nullptr;
	ID3DBlob* error = nullptr;

	// �o�[�b�e�N�X�V�F�[�_�̓ǂݍ���
	if (FAILED(D3DX11CompileFromFile(SHADER_FILE_NAME_TRIANGLE, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &compiledShader, &error, NULL)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(error);

	// �o�[�e�b�N�X�V�F�[�_�̍쐬
	if (FAILED(dxtk.m_device->CreateVertexShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), NULL, &m_pVShader)))
	{
		SAFE_RELEASE(compiledShader);
		return E_FAIL;
	}

	// ���_�̃C���v�b�g���C�A�E�g���`
	D3D11_INPUT_ELEMENT_DESC layout[] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,	D3D11_INPUT_PER_VERTEX_DATA, 0 };
	UINT elements = sizeof(layout) / sizeof(layout[0]);

	// ���_�̃C���v�b�g���C�A�E�g���쐬
	if (FAILED(dxtk.m_device->CreateInputLayout(layout, elements, compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), &shader.m_pInputLayout)))
	{
		return E_FAIL;
	}

	// �s�N�Z���V�F�[�_�̓ǂݍ���
	if (FAILED(D3DX11CompileFromFile(SHADER_FILE_NAME_TRIANGLE, NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &compiledShader, &error, NULL)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(error);

	// �s�N�Z���V�F�[�_�̍쐬
	if (FAILED(dxtk.m_device->CreatePixelShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), NULL, &m_pPShader)))
	{
		SAFE_RELEASE(compiledShader);
		return E_FAIL;
	}
	SAFE_RELEASE(compiledShader);

	// �s��̎󂯓n��
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(Shader::CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	// �R���X�^���g�o�b�t�@�̍쐬
	if (FAILED(dxtk.m_device->CreateBuffer(&cb, NULL, &shader.m_pConstantBuffer)))
	{
		return E_FAIL;
	}

	// ����I��
	return S_OK;
}

/* =====================================================================
//! ���@�e		�`�揈��
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void Figure::Draw()
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Shader& shader = Shader::GetInstance();

	// �s��̍쐬
	D3DXMATRIX world; D3DXMATRIX view; D3DXMATRIX projection;
	D3DXMatrixIdentity(&world);

	// ���[���h�s��֌W�̐ݒ�

	// �r���[�s��֌W�̐ݒ�
	D3DXVECTOR3 eye(0.0f, 1.0f, -2.0f);
	D3DXVECTOR3 lookAt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&view, &eye, &lookAt, &up);

	// �v���W�F�N�V�����s��֌W�̐ݒ�
	D3DXMatrixPerspectiveFovLH(&projection, D3DX_PI / 4, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 110.0f);

	// �V�F�[�_�̃Z�b�g
	dxtk.m_context->VSSetShader(m_pVShader, nullptr, 0);
	dxtk.m_context->GSSetShader(NULL, NULL, 0);
	dxtk.m_context->PSSetShader(m_pPShader, nullptr, 0);

	// �R���X�^���g�o�b�t�@�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE data;
	Shader::CONSTANT_BUFFER cb;

	if (SUCCEEDED(dxtk.m_context->Map(shader.m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data)))
	{
		// �s���n��
		D3DXMATRIX mat = world * view * projection;
		D3DXMatrixTranspose(&mat, &mat);
		cb.mat = mat;

		// �F�̕ύX
		//cb.color = m_vColor;

		memcpy_s(data.pData, data.RowPitch, (void*)(&cb), sizeof(cb));
		dxtk.m_context->Unmap(shader.m_pConstantBuffer, 0);
	}

	// �V�F�[�_�̑I��
	dxtk.m_context->VSSetConstantBuffers(0, 1, &shader.m_pConstantBuffer);
	dxtk.m_context->PSSetConstantBuffers(0, 1, &shader.m_pConstantBuffer);

	// �C���v�b�g���C�A�E�g���Z�b�g
	dxtk.m_context->IASetInputLayout(shader.m_pInputLayout);

	// �v���~�e�B�u�g�|���W�[�̃Z�b�g
	dxtk.m_context->IASetPrimitiveTopology(GetPrimitiveTopology());

	dxtk.m_context->OMSetDepthStencilState(dxtk.m_states->DepthNone(), 0);
	dxtk.m_context->OMSetBlendState(dxtk.m_states->Opaque(), NULL, 0xffffffff);
	dxtk.m_context->RSSetState(dxtk.m_states->CullNone());

	// �v���~�e�B�u��`��
	dxtk.m_context->Draw(GetNumVertex(), 0);
}

/* =====================================================================
//! ���@�e		�I������
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void Figure::Destroy()
{
	SAFE_RELEASE(m_pVShader);
	SAFE_RELEASE(m_pPShader);
}