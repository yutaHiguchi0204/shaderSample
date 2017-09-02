/* =====================================================================
//! @param		「Figure」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/08/20
===================================================================== */

// ヘッダファイルのインクルード
#include "Figure.h"
#include <D3DX11.h>
#include "Constant.h"
#include "DXTKManager.h"
#include "Shader.h"

// 名前空間
using namespace GucchiShader;

/* =====================================================================
//! 内　容		初期化処理（データ）
//! 引　数		なし
//! 戻り値		関数の実行結果（HRESULT）
===================================================================== */
HRESULT Figure::Init3D()
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Shader& shader = Shader::GetInstance();

	// シェーダファイル読み込み
	ID3DBlob* compiledShader = nullptr;
	//D3D11_BLEND_DESC bd;

	// バーテックスシェーダの作成
	if (FAILED(shader.MakeShader(SHADER_FILE_NAME_POINT, "VS", "vs_5_0", (void**)&m_pVShader, &compiledShader)))
	{
		return E_FAIL;
	}

	// 頂点のインプットレイアウトを定義
	D3D11_INPUT_ELEMENT_DESC layout[] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,	D3D11_INPUT_PER_VERTEX_DATA, 0 };
	UINT elements = sizeof(layout) / sizeof(layout[0]);

	// 頂点のインプットレイアウトを作成
	if (FAILED(dxtk.m_device->CreateInputLayout(layout, elements, compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), &shader.m_pInputLayout)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(compiledShader);

	// ピクセルシェーダの作成
	if (FAILED(shader.MakeShader(SHADER_FILE_NAME_POINT, "PS", "ps_5_0", (void**)&m_pPShader, &compiledShader)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(compiledShader);

	// 行列の受け渡し
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(Shader::CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	// コンスタントバッファの作成
	if (FAILED(dxtk.m_device->CreateBuffer(&cb, nullptr, &shader.m_pConstantBuffer)))
	{
		return E_FAIL;
	}

	// 正常終了
	return S_OK;
}

/* =====================================================================
//! 内　容		初期化処理（データ）
//! 引　数		なし
//! 戻り値		関数の実行結果（HRESULT）
===================================================================== */
HRESULT Figure::InitShader()
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Shader& shader = Shader::GetInstance();

	// シェーダファイル読み込み
	ID3DBlob* compiledShader = nullptr;
	ID3DBlob* error = nullptr;

	// バーッテクスシェーダの読み込み
	if (FAILED(D3DX11CompileFromFile(SHADER_FILE_NAME_TRIANGLE, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &compiledShader, &error, NULL)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(error);

	// バーテックスシェーダの作成
	if (FAILED(dxtk.m_device->CreateVertexShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), NULL, &m_pVShader)))
	{
		SAFE_RELEASE(compiledShader);
		return E_FAIL;
	}

	// 頂点のインプットレイアウトを定義
	D3D11_INPUT_ELEMENT_DESC layout[] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,	D3D11_INPUT_PER_VERTEX_DATA, 0 };
	UINT elements = sizeof(layout) / sizeof(layout[0]);

	// 頂点のインプットレイアウトを作成
	if (FAILED(dxtk.m_device->CreateInputLayout(layout, elements, compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), &shader.m_pInputLayout)))
	{
		return E_FAIL;
	}

	// ピクセルシェーダの読み込み
	if (FAILED(D3DX11CompileFromFile(SHADER_FILE_NAME_TRIANGLE, NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &compiledShader, &error, NULL)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(error);

	// ピクセルシェーダの作成
	if (FAILED(dxtk.m_device->CreatePixelShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), NULL, &m_pPShader)))
	{
		SAFE_RELEASE(compiledShader);
		return E_FAIL;
	}
	SAFE_RELEASE(compiledShader);

	// 行列の受け渡し
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(Shader::CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	// コンスタントバッファの作成
	if (FAILED(dxtk.m_device->CreateBuffer(&cb, NULL, &shader.m_pConstantBuffer)))
	{
		return E_FAIL;
	}

	// 正常終了
	return S_OK;
}

/* =====================================================================
//! 内　容		描画処理
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Figure::Draw()
{
	DXTKManager& dxtk = DXTKManager::GetInstance();
	Shader& shader = Shader::GetInstance();

	// 行列の作成
	D3DXMATRIX world; D3DXMATRIX view; D3DXMATRIX projection;
	D3DXMatrixIdentity(&world);

	// ワールド行列関係の設定

	// ビュー行列関係の設定
	D3DXVECTOR3 eye(0.0f, 1.0f, -2.0f);
	D3DXVECTOR3 lookAt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&view, &eye, &lookAt, &up);

	// プロジェクション行列関係の設定
	D3DXMatrixPerspectiveFovLH(&projection, D3DX_PI / 4, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 110.0f);

	// シェーダのセット
	dxtk.m_context->VSSetShader(m_pVShader, nullptr, 0);
	dxtk.m_context->GSSetShader(NULL, NULL, 0);
	dxtk.m_context->PSSetShader(m_pPShader, nullptr, 0);

	// コンスタントバッファに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE data;
	Shader::CONSTANT_BUFFER cb;

	if (SUCCEEDED(dxtk.m_context->Map(shader.m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data)))
	{
		// 行列を渡す
		D3DXMATRIX mat = world * view * projection;
		D3DXMatrixTranspose(&mat, &mat);
		cb.mat = mat;

		// 色の変更
		//cb.color = m_vColor;

		memcpy_s(data.pData, data.RowPitch, (void*)(&cb), sizeof(cb));
		dxtk.m_context->Unmap(shader.m_pConstantBuffer, 0);
	}

	// シェーダの選択
	dxtk.m_context->VSSetConstantBuffers(0, 1, &shader.m_pConstantBuffer);
	dxtk.m_context->PSSetConstantBuffers(0, 1, &shader.m_pConstantBuffer);

	// インプットレイアウトをセット
	dxtk.m_context->IASetInputLayout(shader.m_pInputLayout);

	// プリミティブトポロジーのセット
	dxtk.m_context->IASetPrimitiveTopology(GetPrimitiveTopology());

	dxtk.m_context->OMSetDepthStencilState(dxtk.m_states->DepthNone(), 0);
	dxtk.m_context->OMSetBlendState(dxtk.m_states->Opaque(), NULL, 0xffffffff);
	dxtk.m_context->RSSetState(dxtk.m_states->CullNone());

	// プリミティブを描画
	dxtk.m_context->Draw(GetNumVertex(), 0);
}

/* =====================================================================
//! 内　容		終了処理
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Figure::Destroy()
{
	SAFE_RELEASE(m_pVShader);
	SAFE_RELEASE(m_pPShader);
}