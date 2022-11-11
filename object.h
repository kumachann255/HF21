//=============================================================================
//
// �I�u�W�F�N�g���� [Object.h]
// Author�F 
//=============================================================================
// �I�u�W�F�N�g�̊��N���X(���̃N���X��"�p��"���ăI�u�W�F�N�g�𐶐����܂�)
// �v���n�u�f�[�^( ���f���f�[�^�ǂݍ��� �� ���[�J�����W�̕ϊ� )�������܂��B
//  Draw() �֐��Ń��[���h�}�g���N�X�𐶐����Ă��̂܂܃h���[�R�[�����Ă��܂��B
//  Update()�֐��͌p����Ŏ��R�ɃI�[�o�[���C�h���Ă��������B
//=============================================================================
#pragma once

#include "main.h"
#include "Prefab.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �N���X��`
//*****************************************************************************

class Object
{
private:
	BOOL m_isUse;			// �g�p���t���O

	XMFLOAT3 m_pos;			// ���[���h���W
	XMFLOAT3 m_rot;			// ���[���h��]
	XMFLOAT3 m_scl;			// ���[���h�g�k

	XMMATRIX m_mtxWorld;	// ���[���h�}�g���N�X

protected:
	Prefab *m_prefab;		// �v���n�u�f�[�^( ���f���f�[�^�ǂݍ��� �� ���[�J�����W�̕ϊ� )
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	Object();
	virtual ~Object();

	// �Q�b�^�[�E�Z�b�^�[
	BOOL GetIsUse(void) { return m_isUse; }
	void SetIsUse(BOOL flag) {  m_isUse = flag; }

	virtual void SetPos(XMFLOAT3 pos) { m_pos = pos; }
	XMFLOAT3 GetPos(void) { return m_pos; }
	void SetRot(XMFLOAT3 rot) { m_rot = rot; }
	XMFLOAT3 GetRot(void) { return m_rot; }
	void SetScl(XMFLOAT3 scl) { m_scl = scl; }
	XMFLOAT3 GetScl(void) { return m_scl; }
	void SetSRT(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl) { m_pos = pos; m_rot = rot; m_scl = scl; }

	XMMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	void SetMtxWorld(void) { m_mtxWorld = GetWorldMatrix(m_pos, m_rot, m_scl); }

	void SetPrefab(Prefab * prefab) { m_prefab = prefab; }
	Prefab * GetPrefab(void) { return m_prefab; }
	void SetPrefabPos(XMFLOAT3 pos) { m_prefab->SetPos(pos); }
	void SetPrefabRot(XMFLOAT3 rot) { m_prefab->SetRot(rot); }

	// �����o�֐�
	virtual void Update(void);
	virtual void Draw(void);
};

