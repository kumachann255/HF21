//=============================================================================
//
// �N�G�X�g�{�[�h�}�l�[�W���[���� [QuestBoardManager.h]
// Author : ������n
//
//=============================================================================
#pragma once
#include "QuestBoard.h"
#include "GodObject.h"
#include <vector>
#include "LampManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************

// �N���X���i�[����z��̒�`�iSTL�j
typedef std::vector<QuestBoard*> QuestBoardArray;

class QuestBoardManager :public GodObject
{
private:
	QuestBoardArray BoardArray;
	XMFLOAT3 m_StartPos{ 0.0f ,0.0f,0.0f };
	int m_MakeCnt = 0;		// �o���J�E���g
	int m_colorId[5][3];	// �{�[�h�T��

	int m_failureCount = 0;

	// �����v�̃e�N�X�`���[
	ID3D11ShaderResourceView	*m_Texture[LAMP_TYPE_MAX] = { nullptr };

public:
	QuestBoardManager(God *god);
	~QuestBoardManager();

	QuestBoardArray *GetBoardArray(void) { return &BoardArray; }
	int GetRampColor(void) { BoardArray.size(); }

	void Update(void);
	void Draw(void);

	int GetSerchBoard(int colorType);
	int GetSerchBoardRainbow(void);
};

