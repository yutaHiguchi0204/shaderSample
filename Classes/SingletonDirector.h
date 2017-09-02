/* =====================================================================
//! @param		�uSingletonDirector�v�N���X�̃w�b�_�t�@�C��
//! @create		����@�T��
//! @date		17/07/12
===================================================================== */
#pragma once

// �N���X�̒�`
template <class T> class SingletonDirector
{
public:
	// �C���X�^���X�̐���
	static T& GetInstance()
	{
		static T object;
		return object;
	}

protected:
	// �R���X�g���N�^
	SingletonDirector() {};

private:
	// �R�s�[�Ƒ���h�~
	SingletonDirector(const SingletonDirector &) = delete;
	SingletonDirector& operator=(const SingletonDirector &) = delete;
	SingletonDirector(SingletonDirector &&) = delete;
	SingletonDirector& operator=(SingletonDirector &&) = delete;
};