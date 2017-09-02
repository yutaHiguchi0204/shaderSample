/* =====================================================================
//! @param		�uLineFigure�v�N���X�̃\�[�X�t�@�C��
//! @create		����@�T��
//! @date		17/09/02
===================================================================== */

// �w�b�_�t�@�C���̃C���N���[�h
#include "LineFigure.h"
#include "DXTKManager.h"
#include "Shader.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiShader;

// �����o�֐��̒�`

/* =====================================================================
//! ���@�e		�����������i���f���j
//! ���@��		�Ȃ�
//! �߂�l		�֐��̎��s���ʁiHRESULT�j
===================================================================== */
HRESULT LineFigure::InitFigure()
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Shader& shader = Shader::GetInstance();

	// ���_�f�[�^�쐬
	Vertex vertices[] =
	{
		Vector3(-0.2f, 0.7f, 0.0f),
		Vector3( 0.5f,  0.5f,  0.0f),
	};

	// �o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.ByteWidth = sizeof(Vertex) * NUM_VERTEX_POINT;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.Usage = D3D11_USAGE_DEFAULT;

	// �o�b�t�@�̍쐬
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = vertices;

	if (FAILED(dxtk.m_device->CreateBuffer(&bd, &initData, &shader.m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	// �o�[�e�b�N�X�o�b�t�@���Z�b�g
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	dxtk.m_context->IASetVertexBuffers(0, 1, &shader.m_pVertexBuffer, &stride, &offset);

	return S_OK;
}