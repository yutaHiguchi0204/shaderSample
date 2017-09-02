/* =====================================================================
//! @param		「DXTKManager」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/07/12
===================================================================== */
#pragma once

// ヘッダファイルのインクルード
#include "SingletonDirector.h"

#include <CommonStates.h>
#include <Keyboard.h>
#include <SpriteFont.h>

// クラスの定義
class DXTKManager : public SingletonDirector<DXTKManager>
{
public:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;

	// キーボード関係
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyTracker;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;

	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

private:
	friend class SingletonDirector<DXTKManager>;

	// コンストラクタ
	DXTKManager()
	{
		// キーボード関係の初期化
		m_keyboard = std::make_unique<DirectX::Keyboard>();
		m_keyTracker = std::make_unique <DirectX::Keyboard::KeyboardStateTracker>();
	}

public:

	// 初期化処理
	void Initializer(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		m_device = device;
		m_context = context;

		// コモンステートを作成
		m_states = std::make_unique<DirectX::CommonStates>(device);

		// スプライトバッチ
		m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	}

	// ステートの更新処理
	void UpdateInputState()
	{
		// キー入力情報を取得
		DirectX::Keyboard::State key = m_keyboard->GetState();
		m_keyTracker->Update(key);
	}
};