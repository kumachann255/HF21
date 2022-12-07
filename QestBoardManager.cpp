//=============================================================================
//
// �N�G�X�g�{�[�h�}�l�[�W���[���� [QuestBoardManager.cpp]
// Author : ������n
//
//=============================================================================
#include "QuestBoardManager.h"
#include "input.h"
//#include "debugproc.h"
#include "RollerManager.h"
#include "TrainingCrowManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BOARD_ROTATE_SPEED	(0.001f)		// ��]���x
#define	BOARD_SCL			(5.0f)			// �傫��
#define	MODEL_NAME01		"model_quest_questboard.obj"	// �ǂݍ��ރ��f����
#define BOARD_OFFSET_Y		(70.0f)							// �{�[�h�̑��������킹��
#define BOARD_MAKETIME		(810)							// �{�[�h�̏o������


static char *g_TextureName[LAMP_TYPE_MAX] =
{
	"data/TEXTURE/LAMP/tex_lamp_red.jpg",
	"data/TEXTURE/LAMP/tex_lamp_blue.jpg",
	"data/TEXTURE/LAMP/tex_lamp_green.jpg",
	"data/TEXTURE/LAMP/tex_lamp_yellow.jpg",
	"data/TEXTURE/LAMP/tex_lamp_pink.jpg",
	"data/TEXTURE/LAMP/tex_lamp_purple.jpg",
	"data/TEXTURE/LAMP/tex_lamp_orange.jpg"
};


//=============================================================================
// �R���X�g���N�^�[
//=============================================================================
QuestBoardManager::QuestBoardManager(God *god) :GodObject(god)
{
	// �����v�e�N�X�`���[�̐���
	for (int i = 0; i < LAMP_TYPE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			nullptr,
			nullptr,
			&m_Texture[i],
			nullptr);
	}

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


	// �����v�e�N�X�`���[�̊J��
	for (int i = 0; i < LAMP_TYPE_MAX; i++)
	{
		if (m_Texture[i])
		{
			m_Texture[i]->Release();
			m_Texture[i] = nullptr;
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void QuestBoardManager::Update(void)
{
	float rotX = GetGod()->GetRollerManager()->GetRoller()->GetPrefab()->GetRot().x;
	rotX = XMConvertToDegrees(rotX);
	int AppearRot = (int)(rotX / 45.0f);

	// �J�E���g�̍X�V�ƃ��Z�b�g
	m_MakeCnt += 1;
	if (m_MakeCnt > BOARD_MAKETIME) m_MakeCnt = 0;


	// �J�E���g�l�ɒB������{�[�h���o��������
	if (m_MakeCnt == BOARD_MAKETIME){

		// �o��������W���Z�b�g
		m_StartPos = { -200.0f + (rand() % 280),BOARD_OFFSET_Y,0.0f };

		// ���I�ɐ���
		XMFLOAT3 rot = { 0.0f,0.0f, 0.0f };
		BoardArray.push_back(new QuestBoard(MODEL_NAME01, m_StartPos , rot));

		//=============================================
		/*�����ɃT�E���h�����!!�N�G�X�g�{�[�h�o����*/
		//=============================================

		 //�����v�̃e�N�X�`���[���Z�b�g
		Lamp *pLamp = BoardArray.back()->GetLampManager()->GetLamp();
		int colorId = rand() % 4;	// ���͂S��ނɂ��Ă���

		// �����v�̃e�N�X�`���[��ColorTypeId�̐ݒ�
		for (int i = 0; i < LAMP_MAX; i++)
		{
			int colorId = rand() % 4;
			pLamp[i].SetColorTypeId(colorId);
			pLamp[i].GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[colorId];
		}
	}

	// ��������	(����)
	if (!BoardArray.empty()) {

		// �{�[�h��ԑO�̗v�f���擾
		Lamp *pLamp = BoardArray.front()->GetLampManager()->GetLamp();

		// �����v�̎g�p�t���O���擾
		// �R�̃����v�������Ă�����{�[�h�����ł�����
		if (!pLamp[0].GetIsUse() &&
			!pLamp[1].GetIsUse() &&
			!pLamp[2].GetIsUse() )
		{
			BoardArray.erase(std::cbegin(BoardArray));
			this->GetGod()->GetTrainingCrowManager()->AddStock();

			int probability = rand() % 10;

			if (probability < 2)
			{
				this->GetGod()->GetTrainingCrowManager()->SetSuccess(TRUE);
			}


			//=============================================
			/*�����ɃT�E���h�����!!�N�G�X�g�{�[�h���ŉ�(����)*/
			//=============================================

		}

	}


	// ��������	(���Ԑ؂�)
	if (!BoardArray.empty()){
		// 210�x��]���������
		if(BoardArray[0]->GetRot().x > XMConvertToRadians(210.0f))
		{
			BoardArray.erase(std::cbegin(BoardArray));

			//=============================================
			/*�����ɃT�E���h�����!!�N�G�X�g�{�[�h���ŉ�(���Ԑ؂�)*/
			//=============================================

		}
	}


	for (int i = 0; i < BoardArray.size(); i++)
	{
		BoardArray[i]->Update();

	}

//#ifdef _DEBUG	// �f�o�b�O����\������
//	PrintDebugProc("���[���[�̉�]�p�x %f \n", rotX);
//	PrintDebugProc("���[���[�̉�]�p�x/45.0f =  %d \n", AppearRot);
//#endif

}


//=============================================================================
// �`�揈��
//=============================================================================
void QuestBoardManager::Draw(void)
{
	// ���[���h�}�g���b�N�X�̏�����
	XMMATRIX mtxWorld = XMMatrixIdentity();

	const QuestBoardArray::iterator itEnd = BoardArray.end();

	for (QuestBoardArray::iterator board = BoardArray.begin(); board != itEnd; ++board)
	{
		XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
		rot.x = (*board)->GetRot().x;	// �������g�̉�](0�x����n�߂�������)
		rot.y = GetGod()->GetRollerManager()->GetRoller()->GetPrefab()->GetRot().y;
		rot.z = GetGod()->GetRollerManager()->GetRoller()->GetPrefab()->GetRot().z;


//================================
// �{�[�h�̕`��(���[���[���e)
//================================

		// �e�i���[���[�j�̃��[���h�}�g���N�X����
		mtxWorld = GetWorldMatrix(
			GetGod()->GetRollerManager()->GetRoller()->GetPrefab()->GetPos(),
			rot,
			GetGod()->GetRollerManager()->GetRoller()->GetScl());

		// �{�[�h�̕`��
		(*board)->Draw(mtxWorld);

//================================
// �����v�̕`�揈��(�{�[�h���e)
//================================

		// �e(�{�[�h)�̃��[���h�}�g���N�X����
		mtxWorld = GetWorldMatrix(
			(*board)->GetPos(),
			rot,
			(*board)->GetPrefab()->GetScl());

		// �����v�̕`��
		(*board)->GetLampManager()->Draw(mtxWorld);
	}
}

int QuestBoardManager::GetSerchBoard(int colorType)
{
	//Lamp *lampFlont = BoardArray.front()->GetLampManager()->GetLamp();
	//lampFlont[0].GetColorTypeId;

	for (int i = 0; i < BoardArray.size(); i++)
	{
		if (BoardArray.empty()) continue;

		Lamp *lamp = BoardArray[i]->GetLampManager()->GetLamp();
		for (int p = 0; p < 3; p++)
		{
			if ((lamp[p].GetColorTypeId() == colorType) && (lamp[p].GetIsUse()))
			{
				lamp[p].SetDelete();
				return i;
			}
			
		}
	}

	return LAMP_TYPE_NONE;
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
