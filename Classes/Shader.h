/* =====================================================================
//! @param		「Shader」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/08/20
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "SingletonDirector.h"
#include <d3d11_1.h>
#include <D3DX10.h>
#include <d3dcompiler.h>
#include <SimpleMath.h>

// クラスの定義
namespace GucchiShader
{
	class Shader : public SingletonDirector<Shader>
	{
	public:
		ID3D11InputLayout* m_pInputLayout;
		ID3D11Buffer* m_pConstantBuffer;
		ID3D11Buffer* m_pVertexBuffer;

	public:
		struct CONSTANT_BUFFER
		{
			D3DXMATRIX mat;
			DirectX::SimpleMath::Vector4 color;
		};

	private:
		friend class SingletonDirector<Shader>;

		// コンストラクタ
		Shader() {};

		// デストラクタ
		virtual ~Shader() { Destroy(); }

	public:

		// シェーダの作成
		HRESULT MakeShader(LPSTR shaderFileName, LPSTR shaderFunc, LPSTR profile, void** shaderResource, ID3DBlob** blob);

		// 終了処理
		void Destroy();
	};
}