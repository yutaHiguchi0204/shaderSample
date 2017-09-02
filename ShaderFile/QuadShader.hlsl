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
	float4 color;
};

// バーテックスシェーダ
float4 VS(float4 pos : POSITION) : SV_POSITION
{
	pos = mul(pos, mat);
	return pos;
}

// ピクセルシェーダ
float4 PS(float4 pos : SV_POSITION) : SV_Target
{
	return color;
}