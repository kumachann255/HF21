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
#include "garbageIcon.h"
#include "calendar_num.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MISSION_POINT	(20)
#define MAX_GARBAGE_NUM		(6)
#define BOARD_MAKETIME		(810)							// �{�[�h�̏o������

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Prefab;
class ParticlManager;

// �N���X���i�[����z��̒�`�iSTL�j
typedef std::vector<QuestBoard*> QuestBoardArray;

class QuestBoardManager :public GodObject
{
private:
	QuestBoardArray BoardArray;
	QuestBoard *pQuestBoard = nullptr;
	Prefab *m_pHumanPrefab = nullptr;
	XMFLOAT3 m_StartPos{ 0.0f ,0.0f,0.0f };
	int m_MakeCnt = 0;			// �o���J�E���g
	int m_EffectCnt = 0;		// �G�b�t�F�N�g�����J�E���g
	int m_colorId[5][3];		// �{�[�h�T��
	int m_MaxGarbageCnt = MAX_GARBAGE_NUM;	// �S�~�̏��

	GarbageIcon *m_pGarbageIcon = nullptr;
	int m_MissionPoint = 0;

	int m_Speed = BOARD_MAKETIME;

	// �����v�̃e�N�X�`���[
	ID3D11ShaderResourceView	*m_Texture[LAMP_TYPE_MAX] = { nullptr };
	ParticlManager *pParticlManager = nullptr;

public:
	QuestBoardManager(God *god);
	~QuestBoardManager();

	QuestBoardArray *GetBoardArray(void) { return &BoardArray; }

	int GetRampColor(void) { BoardArray.size(); }

	void Update(void);
	void Draw(void);

	int GetSerchBoard(int colorType);
	int GetSerchBoardRainbow(void);

	void Init();
};

