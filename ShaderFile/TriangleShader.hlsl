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

// �s�N�Z���V�F�[�_�p�\����
struct PS_INPUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

// �o�[�e�b�N�X�V�F�[�_
PS_INPUT VS(float4 pos : POSITION)
{
	PS_INPUT pOut;

	// �v���W�F�N�V�����s��ɕϊ�
	pOut.pos = mul(pos, mat);

	// ���_���ƂɐF�ς�
	if (pos.x > 0.1f)
	{
		pOut.color = float4(1, 0.6, 0.8, 1);
	}
	else if (pos.x < -0.1f)
	{
		pOut.color = float4(1, 0.6, 0.8, 1);
	}
	else
	{
		pOut.color = float4(1, 1, 1, 1);
	}

	return pOut;
}

// �s�N�Z���V�F�[�_
float4 PS(PS_INPUT input) : SV_Target
{
	float4 color = input.color;
	return color;
}