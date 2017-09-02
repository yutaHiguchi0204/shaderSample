/* =====================================================================
//! @param		「LineFigure」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/09/02
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "Figure.h"

// クラスの定義
namespace GucchiShader
{
	class LineFigure : public Figure
	{
	private:
		// 頂点数
		static const UINT NUM_VERTEX_POINT = 2;

	public:
		LineFigure()
		{
			this->InitFigure();
		};
		virtual ~LineFigure() {};

		// モデルの初期化
		HRESULT InitFigure() override;

		// 頂点数の取得
		UINT GetNumVertex() override { return NUM_VERTEX_POINT; }

		// プリミティブトポロジーの取得
		D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology() override { return D3D11_PRIMITIVE_TOPOLOGY_LINELIST; }
	};
}