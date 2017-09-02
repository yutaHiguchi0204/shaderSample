/* =====================================================================
//! @param		�uFigure�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/08/20
===================================================================== */
#pragma once
#pragma warning(disable : 4200)

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <SimpleMath.h>

// �N���X�̒�`
namespace GucchiShader
{
	class Figure
	{
	private:
		ID3D11VertexShader* m_pVShader;			// �o�[�e�b�N�X�V�F�[�_
		ID3D11PixelShader* m_pPShader;			// �s�N�Z���V�F�[�_
		
		DirectX::SimpleMath::Vector4 m_vColor;	// �s�N�Z���J���[

	protected:
		// ���_
		typedef DirectX::SimpleMath::Vector3 Vertex;

	public:
		// �R���X�g���N�^
		Figure()
		{
			//this->Init3D();
			this->InitShader();

			// �����F�Ƃ��č��ɂ��Ă���
			m_vColor = DirectX::SimpleMath::Vector4(0, 0, 0, 1);
		}
		virtual ~Figure() {};

		// ����������
		virtual HRESULT Init3D();
		virtual HRESULT InitShader();
		virtual HRESULT InitFigure() = 0;

		// ���_���̎擾
		virtual UINT GetNumVertex() = 0;

		// �v���~�e�B�u�g�|���W�[�̎擾
		virtual D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology() = 0;

		// �`�揈��
		virtual void Draw();

		// �I������
		virtual void Destroy();
	};
}