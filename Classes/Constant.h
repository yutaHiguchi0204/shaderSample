/* =====================================================================
//! @param		�萔�w�b�_
//! @create		����@�T��
//! @date		17/08/20
===================================================================== */
#pragma once

/* �萔 */

// �T�C�Y
const float		WINDOW_WIDTH		= 800.0f;
const float		WINDOW_HEIGHT		= 600.0f;

// �t�@�C����
const LPSTR		SHADER_FILE_NAME_POINT		=  "ShaderFile/PointShader.hlsl";
const LPSTR		SHADER_FILE_NAME_LINE		=  "ShaderFile/LineShader.hlsl";
const LPWSTR	SHADER_FILE_NAME_TRIANGLE	= L"ShaderFile/TriangleShader.hlsl";

/* �}�N���萔 */

// ����֌W
#define SAFE_DELETE(obj)		if (obj) { delete (obj); (obj) = nullptr; }
#define SAFE_DELETE_ARR(obj)	if (obj) { delete[] (obj); (obj) = nullptr; }
#define SAFE_RELEASE(obj)		if (obj) { obj->Release(); obj = nullptr; }

// ���̑��V�X�e��
#define MEM_ALIGN_16B			_declspec(align(16))