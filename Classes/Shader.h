/* =====================================================================
//! @param		�uShader�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/08/20
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "SingletonDirector.h"
#include <d3d11_1.h>
#include <D3DX10.h>
#include <d3dcompiler.h>
#include <SimpleMath.h>

// �N���X�̒�`
namespace GucchiShader
{
	class Shader : public SingletonDirector<Shader>
	{
	public:
		ID3D11InputLayout* m_pInputLayout;
		ID3D11Buffer* m_pConstantBuffer;
		ID3D11Buffer* m_pVertexBuffer;

	public:
		struct CONSTANT_BUFFER
		{
			D3DXMATRIX mat;
			DirectX::SimpleMath::Vector4 color;
		};

	private:
		friend class SingletonDirector<Shader>;

		// �R���X�g���N�^
		Shader() {};

		// �f�X�g���N�^
		virtual ~Shader() { Destroy(); }

	public:

		// �V�F�[�_�̍쐬
		HRESULT MakeShader(LPSTR shaderFileName, LPSTR shaderFunc, LPSTR profile, void** shaderResource, ID3DBlob** blob);

		// �I������
		void Destroy();
	};
}