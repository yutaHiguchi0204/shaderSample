/* =====================================================================
//! @param		�V�F�[�_�t�@�C��
//! @create		����@�T��
//! @date		17/08/20
===================================================================== */

// �O���[�o�����
cbuffer Global
{
	// �ϊ��s��
	matrix mat;
	float4 color;
};

// �o�[�e�b�N�X�V�F�[�_
float4 VS(float4 pos : POSITION) : SV_POSITION
{
	pos = mul(pos, mat);
	return pos;
}

// �s�N�Z���V�F�[�_
float4 PS(float4 pos : SV_POSITION) : SV_Target
{
	return color;
}