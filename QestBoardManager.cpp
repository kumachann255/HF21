//=============================================================================
//
// �N�G�X�g�{�[�h�}�l�[�W���[���� [QuestBoardManager.cpp]
// Author : ������n
//
//=============================================================================
#include "QuestBoardManager.h"
#include "input.h"
#include "debugproc.h"
#include "Roller.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BOARD_ROTATE_SPEED	(0.001f)		// ��]���x
#define	BOARD_SCL			(5.0f)			// �傫��
#define	MODEL_NAME01		"model_quest_gomi_01.obj"	// �ǂݍ��ރ��f����


//=============================================================================
// �R���X�g���N�^�[
//=============================================================================
QuestBoardManager::QuestBoardManager(God *god) :GodObject(god)
{

}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
QuestBoardManager::~QuestBoardManager()
{
	const QuestBoardArray::iterator itEnd = BoardArray.end();

	for (QuestBoardArray::iterator it = BoardArray.begin(); it != itEnd; ++it) {
		delete *it;
	}

	BoardArray.clear();

}

//=============================================================================
// �X�V����
//=============================================================================
void QuestBoardManager::Update(void)
{
	if (GetKeyboardTrigger(DIK_F5))
	{
		m_StartPos = { 0.0f + (rand()%100),70.0f,0.0f };
		BoardArray.push_back(new QuestBoard(MODEL_NAME01, m_StartPos));
	}

	if (GetKeyboardTrigger(DIK_F6))
	{
		BoardArray.erase(std::cbegin(BoardArray));
	}

	const QuestBoardArray::iterator itEnd = BoardArray.end();

	for (QuestBoardArray::iterator it = BoardArray.begin(); it != itEnd; ++it)
	{
		(*it)->Update();
	}


#ifdef _DEBUG	// �f�o�b�O����\������
	PrintDebugProc("Board.Size:%d\n", BoardArray.size());
	//PrintDebugProc("BoardArray.back().GetIsUse():%d\n", BoardArray.back().GetIsUse());
#endif

}


//=============================================================================
// �`�揈��
//=============================================================================
void QuestBoardManager::Draw(void)
{

	// ���[���h�}�g���b�N�X�̏�����
	XMMATRIX mtxWorld = XMMatrixIdentity();

	const QuestBoardArray::iterator itEnd = BoardArray.end();

	for (QuestBoardArray::iterator it = BoardArray.begin(); it != itEnd; ++it) 
	{
		// �e�i���[���[�j�̃��[���h�}�g���N�X����
		mtxWorld = GetWorldMatrix(
			GetGod()->GetRoller()->GetPrefab()->GetPos(),
			GetGod()->GetRoller()->GetPrefab()->GetRot(),
			GetGod()->GetRoller()->GetScl());

		(*it)->Draw(mtxWorld);
	}
}



//=============================================================================
// <vector>��for���L�q����
//=============================================================================
/*

std::vector<QuestBoard>::iterator itr;     // vector<QuestBoard> �̗v�f�ւ̃C�e���[�^
std::vector<QuestBoard>::iterator itr = BoardArray.begin();   // �ŏ��̗v�f���w���C�e���[�^
auto itr = BoardArray.begin();   // �ŏ��̗v�f���w���C�e���[�^

[1]
for (auto itr = BoardArray.begin(); itr != BoardArray.end(); ++itr) 
{

	(*itr).Draw();

}

[2]
for (int i=0; i < BoardArray.size(); i++)
{
	BoardArray[i].Draw();

}

[3]
for (QuestBoard& Board : BoardArray)
{
	Board.Draw();
}																		

*/

//=============================================================================
// <vector>�̎g����
//=============================================================================
//�����̗v�f����菜���ɂ́Apop_back�֐����g���܂��B
//back�֐����g���ƁA�����̗v�f�ɃA�N�Z�X���邱�Ƃ��ł��܂�
//�C�ӂ̗v�f����菜���ɂ́Aerase�֐����g���܂��B
// v.erase(std::cbegin(v) + 1);�ŗv�f�P���폜

//�y�A�����Ă��镡���̗v�f���܂Ƃ߂Ď�菜���z
//�I���ʒu������킷�ɂ́u�P���v���w���悤
//v.erase(std::cbegin(v), std::cbegin(v) + 2);�ɂ��邱�Ƃɒ��ӂ��Ă��������B0��1���폜
