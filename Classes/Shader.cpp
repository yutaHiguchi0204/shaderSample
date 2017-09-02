/* =====================================================================
//! @param		「Shader」クラスのソースファイル
//! @create		樋口　裕太
//! @date		17/08/20
===================================================================== */

// ヘッダファイルのインクルード
#include "Shader.h"
#include <D3DX11.h>
#include "Constant.h"
#include "DXTKManager.h"

// 名前空間
using namespace GucchiShader;

/* =====================================================================
//! 内　容		シェーダの作成
//! 引　数		
//! 戻り値		関数の実行結果（HRESULT）
===================================================================== */
HRESULT Shader::MakeShader(LPSTR shaderFileName, LPSTR shaderFunc, LPSTR profile, void** shaderResource, ID3DBlob** blob)
{
	DXTKManager& dxtk = DXTKManager::GetInstance();

	ID3DBlob* error = nullptr;

	// シェーダファイルを読み込む
	if (FAILED(D3DX11CompileFromFileA(shaderFileName, nullptr, nullptr, shaderFunc, profile, D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 0, nullptr, blob, &error, nullptr)))
	{
		// エラー処理
		char* p = (char*)(error->GetBufferPointer());
		MessageBoxA(0, p, 0, MB_OK);
		return E_FAIL;
	}

	// 読み込めなかった場合安全なリリースを行う
	SAFE_RELEASE(error);

	char szProfile[8] = { 0 };
	memcpy(szProfile, profile, 2);

	// シェーダの登録
	if (strcmp(szProfile, "vs") == 0)
	{
		// バーテックスシェーダの登録
		if (FAILED(dxtk.m_device->CreateVertexShader((*blob)->GetBufferPointer(), (*blob)->GetBufferSize(), nullptr, (ID3D11VertexShader**)shaderResource)))
			return E_FAIL;
	}
	if (strcmp(szProfile, "ps") == 0)
	{
		// ピクセルシェーダの登録
		if (FAILED(dxtk.m_device->CreatePixelShader((*blob)->GetBufferPointer(), (*blob)->GetBufferSize(), nullptr, (ID3D11PixelShader**)shaderResource)))
			return E_FAIL;
	}

	return S_OK;
}

/* =====================================================================
//! 内　容		終了処理
//! 引　数		なし
//! 戻り値		なし
===================================================================== */
void Shader::Destroy()
{
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pVertexBuffer);
}
