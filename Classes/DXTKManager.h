/* =====================================================================
//! @param		�uDXTKManager�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/07/12
===================================================================== */
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include "SingletonDirector.h"

#include <CommonStates.h>
#include <Keyboard.h>
#include <SpriteFont.h>

// �N���X�̒�`
class DXTKManager : public SingletonDirector<DXTKManager>
{
public:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;

	// �L�[�{�[�h�֌W
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyTracker;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;

	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

private:
	friend class SingletonDirector<DXTKManager>;

	// �R���X�g���N�^
	DXTKManager()
	{
		// �L�[�{�[�h�֌W�̏�����
		m_keyboard = std::make_unique<DirectX::Keyboard>();
		m_keyTracker = std::make_unique <DirectX::Keyboard::KeyboardStateTracker>();
	}

public:

	// ����������
	void Initializer(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		m_device = device;
		m_context = context;

		// �R�����X�e�[�g���쐬
		m_states = std::make_unique<DirectX::CommonStates>(device);

		// �X�v���C�g�o�b�`
		m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	}

	// �X�e�[�g�̍X�V����
	void UpdateInputState()
	{
		// �L�[���͏����擾
		DirectX::Keyboard::State key = m_keyboard->GetState();
		m_keyTracker->Update(key);
	}
};