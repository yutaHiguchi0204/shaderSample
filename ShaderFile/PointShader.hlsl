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
};

// �\����
struct SHADER_INPUT
{
	float4 pos : SV_POSITION;
};

// �o�[�e�b�N�X�V�F�[�_
SHADER_INPUT VS(float4 pos : POSITION) : SV_POSITION
{
	SHADER_INPUT shaderOut;
	shaderOut.pos = mul(pos, mat);
	return shaderOut;
}

// �s�N�Z���V�F�[�_
float4 PS(SHADER_INPUT input) : SV_Target
{
	return float4(0, 0, 0, 1);
}