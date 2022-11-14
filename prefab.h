//=============================================================================
//
// �v���n�u [prefab.h]
// Author�F ������n
//=============================================================================
// Object�N���X�������ʂ̃f�[�^
// ��Ƀ��f���f�[�^�̓ǂݍ��݂ƃ��[�J�����W�̐ݒ�Ɏg��
// �����[�J���̉�]�͂悭�g��
//=============================================================================
#pragma once
#include"model.h"
#include <string> 

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �N���X��`
//*****************************************************************************


class Prefab
{
	BOOL m_isLoadModel;	// ���f���ǂݍ��ݍς݃t���O

	XMFLOAT3 m_pos;		// ���[�J�����W
	XMFLOAT3 m_rot;		// ���[�J����]
	XMFLOAT3 m_scl;		// ���[�J���g�k

	std::string m_name;	// �t�@�C����
	DX11_MODEL m_model;	// ���f���f�[�^

public:
	Prefab();	
	~Prefab();	

	// �Q�b�^�[�E�Z�b�^�[
	void SetModel(std::string modelName);		// ���f���ǂݍ���

	BOOL GetIsLoad(void) { return m_isLoadModel; }
	void SetIsLoad(BOOL flag) {  m_isLoadModel = flag; }

	void SetPos(XMFLOAT3 pos) { m_pos = pos; }
	XMFLOAT3 GetPos(void) { return m_pos; }
	void SetRot(XMFLOAT3 rot) { m_rot = rot; }
	XMFLOAT3 GetRot(void) { return m_rot; }
	void SetScl(XMFLOAT3 scl) { m_scl = scl; }
	XMFLOAT3 GetScl(void) { return m_scl; }

	void SetName(std::string name) { m_name = name; }
	void SetColor(XMFLOAT4 color);

	DX11_MODEL * GetModel(void) { return &m_model; }
	XMMATRIX GetMtxWorld(void) { return GetWorldMatrix(m_pos, m_rot, m_scl); }
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
