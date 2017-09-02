/* =====================================================================
//! @param		「LineFigure」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/09/02
===================================================================== */

// ヘッダファイルのインクルード
#include "LineFigure.h"
#include "DXTKManager.h"
#include "Shader.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace GucchiShader;

// メンバ関数の定義

/* =====================================================================
//! 内　容		初期化処理（モデル）
//! 引　数		なし
//! 戻り値		関数の実行結果（HRESULT）
===================================================================== */
HRESULT LineFigure::InitFigure()
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Shader& shader = Shader::GetInstance();

	// 頂点データ作成
	Vertex vertices[] =
	{
		Vector3(-0.2f, 0.7f, 0.0f),
		Vector3( 0.5f,  0.5f,  0.0f),
	};

	// バッファの設定
	D3D11_BUFFER_DESC bd;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.ByteWidth = sizeof(Vertex) * NUM_VERTEX_POINT;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.Usage = D3D11_USAGE_DEFAULT;

	// バッファの作成
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = vertices;

	if (FAILED(dxtk.m_device->CreateBuffer(&bd, &initData, &shader.m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	// バーテックスバッファをセット
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	dxtk.m_context->IASetVertexBuffers(0, 1, &shader.m_pVertexBuffer, &stride, &offset);

	return S_OK;
}