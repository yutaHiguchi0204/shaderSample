/* =====================================================================
//! @param		「TriangleFigure」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/09/02
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "Figure.h"
#include "Constant.h"

// クラスの定義
namespace GucchiShader
{
	class TriangleFigure : public Figure
	{
	private:
		// 頂点数
		static const UINT NUM_VERTEX_POINT = 3;

	public:
		TriangleFigure()
		{
			this->InitFigure();
		};
		virtual ~TriangleFigure() {};

		// モデルの初期化
		HRESULT InitFigure() override;

		// 頂点数の取得
		UINT GetNumVertex() override { return NUM_VERTEX_POINT; }

		// プリミティブトポロジーの取得
		D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology() override { return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST; }
	};
}