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
#include "slotManager.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BOARD_ROTATE_SPEED	(0.001f)		// ��]���x
#define	BOARD_SCL			(5.0f)			// �傫��
#define	MODEL_NAME01		"model_questboard_garbage02.obj"	// �ǂݍ��ރ��f����
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

	m_pGarbageIcon = new GarbageIcon();
	m_pCalendarNum = new CalendarNum();

	XMFLOAT3 rot = { 0.0f, 3.14f, 0.0f };
	pQuestBoard = new QuestBoard(MODEL_NAME01, m_StartPos, rot);

}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
QuestBoardManager::~QuestBoardManager()
{
	BoardArray.clear();

	for (size_t i = 0; i < BoardArray.size(); i++)
	{
		delete BoardArray[i];
	}

	// �����v�e�N�X�`���[�̊J��
	for (int i = 0; i < LAMP_TYPE_MAX; i++)
	{
		if (m_Texture[i])
		{
			m_Texture[i]->Release();
			m_Texture[i] = nullptr;
		}
	}

	delete m_pGarbageIcon;
	delete m_pCalendarNum;
	delete pQuestBoard;
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
		XMFLOAT3 rot = { 0.0f, 3.14f, 0.0f };
		BoardArray.push_back(new QuestBoard( m_StartPos , rot));

		switch (rand() % 2)
		{
		case 0:
			PlaySound(SOUND_LABEL_SE_se_quest_pop_0); // �N�G�X�g�o��
			break;

		case 1:
			PlaySound(SOUND_LABEL_SE_se_quest_pop_1); // �N�G�X�g�o��
			break;
		}

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

	// ���f�����Z�b�g
	for (int i = 0; i < BoardArray.size(); i++)
	{
		if (BoardArray.empty()) return;

		DX11_MODEL model = pQuestBoard->GetPrefab()->GetModelDate();
		BoardArray[i]->GetPrefab()->SetModelDate(model);
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

			switch (rand() % 4)
			{
			case 0:
				PlaySound(SOUND_LABEL_SE_se_mens_hihi); // �N�G�X�g�B��
				break;

			case 1:
				PlaySound(SOUND_LABEL_SE_se_mens_ou); // �N�G�X�g�B��
				break;

			case 2:
				PlaySound(SOUND_LABEL_SE_se_mens_yei); // �N�G�X�g�B��
				break;

			case 3:
				PlaySound(SOUND_LABEL_SE_se_women_ou); // �N�G�X�g�B��
				break;
			}

			if (!this->GetGod()->GetSlotManager()->GetRainbow())
			{
				this->GetGod()->GetTrainingCrowManager()->AddStock();
			}

			int probability = rand() % 10;

			if (probability - m_failureCount < 2)
			{
				m_failureCount = 0;
				this->GetGod()->GetTrainingCrowManager()->SetSuccess(TRUE);
			}
			else
			{
				m_failureCount++;
			}

			m_MissionPoint--;

		}
	}

	m_pGarbageIcon->SetIconNum(m_MissionPoint);
	m_pGarbageIcon->Update();

	m_pCalendarNum->Update();

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

	for (size_t i = 0; i < BoardArray.size(); i++)
	{
		if (BoardArray.empty()) return;

		XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
		rot.x = BoardArray[i]->GetRot().x;	// �������g�̉�](0�x����n�߂�������)
		rot.y = GetGod()->GetRollerManager()->GetRoller()->GetPrefab()->GetRot().y;
		rot.z = GetGod()->GetRollerManager()->GetRoller()->GetPrefab()->GetRot().z;


		//================================
		// �{�[�h�̕`��(���[���[���e)
		//================================

				// �e�i���[���[�j�̃��[���h�}�g���N�X����
		mtxWorld = GetWorldMatrix(
			GetGod()->GetRollerManager()->GetRoller()->GetPrefab()->GetPos(),
			rot,
			//GetGod()->GetRollerManager()->GetRoller()->GetScl());
			XMFLOAT3(1.0f, 1.0f, 1.0f));

		// �{�[�h�̕`��
		BoardArray[i]->Draw(mtxWorld);

		//================================
		// �����v�̕`�揈��(�{�[�h���e)
		//================================

				// �e(�{�[�h)�̃��[���h�}�g���N�X����
		mtxWorld = GetWorldMatrix(
			BoardArray[i]->GetPos(),
			rot,
			XMFLOAT3(1.0f, 1.0f, 1.0f));

		// �t�H���V�F�[�_�[�֕ύX
		//SetShader(SHADER_MODE_PHONG);
		//SetViewPort(TYPE_LEFT_HALF_SCREEN);
		//SetCameraAT(XMFLOAT3(0.0f,0.0f,0.0f));
		//SetCamera();


		// �����v�̕`��
		BoardArray[i]->GetLampManager()->Draw(mtxWorld);
	}

	m_pGarbageIcon->Draw();
	m_pCalendarNum->Draw();
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
			if ((lamp[p].GetColorTypeId() == colorType) && (lamp[p].GetIsUse()) && (!lamp[p].GetDelete()))
			{
				lamp[p].SetDelete(TRUE);
				PlaySound(SOUND_LABEL_SE_se_lamp_clear);
				
				return i;
			}
		}
	}

	return LAMP_TYPE_NONE;
}

int QuestBoardManager::GetSerchBoardRainbow(void)
{
	for (int i = 0; i < BoardArray.size(); i++)
	{
		if (BoardArray.empty()) continue;

		Lamp *lamp = BoardArray[i]->GetLampManager()->GetLamp();
		for (int p = 0; p < 3; p++)
		{
			if ((lamp[p].GetIsUse()) && (!lamp[p].GetDelete()))
			{
				lamp[p].SetDelete(TRUE);
				return i;
			}
		}
	}

	return LAMP_TYPE_NONE;
}
