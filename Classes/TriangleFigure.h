/* =====================================================================
//! @param		�uTriangleFigure�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/09/02
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "Figure.h"
#include "Constant.h"

// �N���X�̒�`
namespace GucchiShader
{
	class TriangleFigure : public Figure
	{
	private:
		// ���_��
		static const UINT NUM_VERTEX_POINT = 3;

	public:
		TriangleFigure()
		{
			this->InitFigure();
		};
		virtual ~TriangleFigure() {};

		// ���f���̏�����
		HRESULT InitFigure() override;

		// ���_���̎擾
		UINT GetNumVertex() override { return NUM_VERTEX_POINT; }

		// �v���~�e�B�u�g�|���W�[�̎擾
		D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology() override { return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST; }
	};
}