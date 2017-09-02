/* =====================================================================
//! @param		シェーダファイル
//! @create		樋口　裕太
//! @date		17/08/20
===================================================================== */

// グローバル情報
cbuffer Global
{
	// 変換行列
	matrix mat;
};

// 構造体
struct SHADER_INPUT
{
	float4 pos : SV_POSITION;
};

// バーテックスシェーダ
SHADER_INPUT VS(float4 pos : POSITION) : SV_POSITION
{
	SHADER_INPUT shaderOut;
	shaderOut.pos = mul(pos, mat);
	return shaderOut;
}

// ピクセルシェーダ
float4 PS(SHADER_INPUT input) : SV_Target
{
	return float4(0, 0, 0, 1);
}