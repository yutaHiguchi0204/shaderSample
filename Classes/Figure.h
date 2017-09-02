/* =====================================================================
//! @param		「Figure」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/08/20
===================================================================== */
#pragma once
#pragma warning(disable : 4200)

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <SimpleMath.h>

// クラスの定義
namespace GucchiShader
{
	class Figure
	{
	private:
		ID3D11VertexShader* m_pVShader;			// バーテックスシェーダ
		ID3D11PixelShader* m_pPShader;			// ピクセルシェーダ
		
		DirectX::SimpleMath::Vector4 m_vColor;	// ピクセルカラー

	protected:
		// 頂点
		typedef DirectX::SimpleMath::Vector3 Vertex;

	public:
		// コンストラクタ
		Figure()
		{
			//this->Init3D();
			this->InitShader();

			// 初期色として黒にしておく
			m_vColor = DirectX::SimpleMath::Vector4(0, 0, 0, 1);
		}
		virtual ~Figure() {};

		// 初期化処理
		virtual HRESULT Init3D();
		virtual HRESULT InitShader();
		virtual HRESULT InitFigure() = 0;

		// 頂点数の取得
		virtual UINT GetNumVertex() = 0;

		// プリミティブトポロジーの取得
		virtual D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology() = 0;

		// 描画処理
		virtual void Draw();

		// 終了処理
		virtual void Destroy();
	};
}