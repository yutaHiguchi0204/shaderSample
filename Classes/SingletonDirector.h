/* =====================================================================
//! @param		「SingletonDirector」クラスのヘッダファイル
//! @create		樋口　裕太
//! @date		17/07/12
===================================================================== */
#pragma once

// クラスの定義
template <class T> class SingletonDirector
{
public:
	// インスタンスの生成
	static T& GetInstance()
	{
		static T object;
		return object;
	}

protected:
	// コンストラクタ
	SingletonDirector() {};

private:
	// コピーと代入防止
	SingletonDirector(const SingletonDirector &) = delete;
	SingletonDirector& operator=(const SingletonDirector &) = delete;
	SingletonDirector(SingletonDirector &&) = delete;
	SingletonDirector& operator=(SingletonDirector &&) = delete;
};