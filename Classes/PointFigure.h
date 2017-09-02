/* =====================================================================
//! @param		�uPointFigure�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/08/20
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "Figure.h"

// �N���X�̒�`
namespace GucchiShader
{
	class PointFigure : public Figure
	{
	private:
		// ���_��
		static const UINT NUM_VERTEX_POINT = 1;

	public:
		PointFigure()
		{
			this->InitFigure();
		};
		virtual ~PointFigure() {};

		// ���f���̏�����
		HRESULT InitFigure() override;

		// ���_���̎擾
		UINT GetNumVertex() override { return NUM_VERTEX_POINT; }

		// �v���~�e�B�u�g�|���W�[�̎擾
		D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology() override { return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST; }
	};
}