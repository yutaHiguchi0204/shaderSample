/* =====================================================================
//! @param		�uShader�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/08/20
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "Shader.h"
#include <D3DX11.h>
#include "Constant.h"
#include "DXTKManager.h"

// ���O���
using namespace GucchiShader;

/* =====================================================================
//! ���@�e		�V�F�[�_�̍쐬
//! ���@��		
//! �߂�l		�֐��̎��s���ʁiHRESULT�j
===================================================================== */
HRESULT Shader::MakeShader(LPSTR shaderFileName, LPSTR shaderFunc, LPSTR profile, void** shaderResource, ID3DBlob** blob)
{
	DXTKManager& dxtk = DXTKManager::GetInstance();

	ID3DBlob* error = nullptr;

	// �V�F�[�_�t�@�C����ǂݍ���
	if (FAILED(D3DX11CompileFromFileA(shaderFileName, nullptr, nullptr, shaderFunc, profile, D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 0, nullptr, blob, &error, nullptr)))
	{
		// �G���[����
		char* p = (char*)(error->GetBufferPointer());
		MessageBoxA(0, p, 0, MB_OK);
		return E_FAIL;
	}

	// �ǂݍ��߂Ȃ������ꍇ���S�ȃ����[�X���s��
	SAFE_RELEASE(error);

	char szProfile[8] = { 0 };
	memcpy(szProfile, profile, 2);

	// �V�F�[�_�̓o�^
	if (strcmp(szProfile, "vs") == 0)
	{
		// �o�[�e�b�N�X�V�F�[�_�̓o�^
		if (FAILED(dxtk.m_device->CreateVertexShader((*blob)->GetBufferPointer(), (*blob)->GetBufferSize(), nullptr, (ID3D11VertexShader**)shaderResource)))
			return E_FAIL;
	}
	if (strcmp(szProfile, "ps") == 0)
	{
		// �s�N�Z���V�F�[�_�̓o�^
		if (FAILED(dxtk.m_device->CreatePixelShader((*blob)->GetBufferPointer(), (*blob)->GetBufferSize(), nullptr, (ID3D11PixelShader**)shaderResource)))
			return E_FAIL;
	}

	return S_OK;
}

/* =====================================================================
//! ���@�e		�I������
//! ���@��		�Ȃ�
//! �߂�l		�Ȃ�
===================================================================== */
void Shader::Destroy()
{
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pVertexBuffer);
}
