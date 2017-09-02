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

// ピクセルシェーダ用構造体
struct PS_INPUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

// バーテックスシェーダ
PS_INPUT VS(float4 pos : POSITION)
{
	PS_INPUT pOut;

	// プロジェクション行列に変換
	pOut.pos = mul(pos, mat);

	// 頂点ごとに色変え
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

// ピクセルシェーダ
float4 PS(PS_INPUT input) : SV_Target
{
	float4 color = input.color;
	return color;
}