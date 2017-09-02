/* =====================================================================
//! @param		定数ヘッダ
//! @create		樋口　裕太
//! @date		17/08/20
===================================================================== */
#pragma once

/* 定数 */

// サイズ
const float		WINDOW_WIDTH		= 800.0f;
const float		WINDOW_HEIGHT		= 600.0f;

// ファイル名
const LPSTR		SHADER_FILE_NAME_POINT		=  "ShaderFile/PointShader.hlsl";
const LPSTR		SHADER_FILE_NAME_LINE		=  "ShaderFile/LineShader.hlsl";
const LPWSTR	SHADER_FILE_NAME_TRIANGLE	= L"ShaderFile/TriangleShader.hlsl";

/* マクロ定数 */

// 解放関係
#define SAFE_DELETE(obj)		if (obj) { delete (obj); (obj) = nullptr; }
#define SAFE_DELETE_ARR(obj)	if (obj) { delete[] (obj); (obj) = nullptr; }
#define SAFE_RELEASE(obj)		if (obj) { obj->Release(); obj = nullptr; }

// その他システム
#define MEM_ALIGN_16B			_declspec(align(16))