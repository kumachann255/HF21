//=============================================================================
//
// �N�G�X�g�{�[�h�}�l�[�W���[���� [QuestBoardManager.cpp]
// Author : ������n
//
//=============================================================================
#include "QuestBoardManager.h"
#include "input.h"
#include "debugproc.h"
#include "RollerManager.h"
#include "TrainingCrowManager.h"
#include "slotManager.h"
#include "sound.h"
#include "Stage_01.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BOARD_ROTATE_SPEED	(0.001f)		// ��]���x
#define	BOARD_SCL			(5.0f)			// �傫��
#define	MODEL_NAME01		"model_questboard_garbage02.obj"	// �ǂݍ��ރ��f����
#define	MODEL_NAME02		"model_human.obj"					// �ǂݍ��ރ��f����
#define BOARD_OFFSET_Y		(70.0f)							// �{�[�h�̑��������킹��

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

	XMFLOAT3 rot = { 0.0f, 3.14f, 0.0f };
	pQuestBoard = new QuestBoard(MODEL_NAME01, m_StartPos, rot);

	m_pHumanPrefab = new Prefab;
	m_pHumanPrefab->SetModel(MODEL_NAME02);
	pParticlManager = new ParticlManager();

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
	delete pQuestBoard;
	delete m_pHumanPrefab;
	delete pParticlManager;
}

//=============================================================================
// �X�V����
//=============================================================================
void QuestBoardManager::Update(void)
{
	// ��������	(����)
	if (!BoardArray.empty()) {

		for (int i = 0; i < BoardArray.size(); i++)
		{
			Lamp *pLamp = BoardArray[i]->GetLampManager()->GetLamp();

			// �����v�̎g�p�t���O���擾
			// �R�̃����v�������Ă�����{�[�h�����ł�����
			if (!pLamp[0].GetIsUse() &&
				!pLamp[1].GetIsUse() &&
				!pLamp[2].GetIsUse() && !BoardArray[i]->GetChangeModelFlag())
			{
				//BoardArray.erase(std::cbegin(BoardArray));

				BoardArray[i]->SetDeleteFlag(TRUE);


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

				m_MissionPoint++;

			}
		}
	}

	// ��������	(���Ԑ؂�)
	if (!BoardArray.empty()) {
		// 210�x��]���������
		if (BoardArray[0]->GetRot().x > XMConvertToRadians(210.0f))
		{
			BoardArray.erase(std::cbegin(BoardArray));
		}
	}

	m_pGarbageIcon->SetIconNum(m_MissionPoint);
	m_pGarbageIcon->Update();
	pParticlManager->Update();

	for (int i = 0; i < BoardArray.size(); i++)
	{
		BoardArray[i]->Update();
	}

	// �J�E���g�̍X�V�ƃ��Z�b�g
	m_MakeCnt += 1;
	if (m_MakeCnt > m_Speed) m_MakeCnt = 0;

	auto arraySize = BoardArray.size();

	// �J�E���g�l�ɒB������{�[�h���o��������
	if (m_MakeCnt == m_Speed &&
		m_MaxGarbageCnt >= arraySize)
	{
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

		// �����v�̃e�N�X�`���[��ColorTypeId�̐ݒ�
		for (int i = 0; i < LAMP_MAX; i++)
		{
			int colorId = rand() % 4;	// ���͂S��ނɂ��Ă���
			pLamp[i].SetColorTypeId(colorId);
			pLamp[i].GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[colorId];
		}
	}

	arraySize = BoardArray.size();
	int changeCnt = 0;
	int deleteCnt = 0;

	// �S�~�̐����J�E���g
	if (arraySize >= 2 &&			  // �Q�ȏ゠��
		m_MaxGarbageCnt >= arraySize) // ����l�����������Ƃ�
	{
		for (int i = 0; i < BoardArray.size(); i++)
		{
			if (BoardArray[i]->GetDeleteFlag()) {

				deleteCnt++;
			}
		}

		// �S�~2�ȉ��̎��o��������
		if ((arraySize - deleteCnt) <= 1)
		{
			// �o��������W���Z�b�g
			m_StartPos = { -200.0f + (rand() % 280),BOARD_OFFSET_Y,0.0f };

			// ���I�ɐ���
			XMFLOAT3 rot = { 0.0f, 3.14f, 0.0f };
			BoardArray.push_back(new QuestBoard(m_StartPos, rot));

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

			// �����v�̃e�N�X�`���[��ColorTypeId�̐ݒ�
			for (int i = 0; i < LAMP_MAX; i++)
			{
				int colorId = rand() % 4;	// ���͂S��ނɂ��Ă���
				pLamp[i].SetColorTypeId(colorId);
				pLamp[i].GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[colorId];
			}

		}

	}


	// ���f�����Z�b�g
	for (int i = 0; i < BoardArray.size(); i++)
	{
		if (BoardArray.empty()) return;

		if (BoardArray[i]->GetDeleteFlag()&& !BoardArray[i]->GetChangeModelFlag())
		{// �j��t���O����������l�̃��f���ɕς���
			DX11_MODEL model = m_pHumanPrefab->GetModelDate();

			BoardArray[i]->GetPrefab()->SetModelDate(model);
			BoardArray[i]->SetChangeModelFlag(TRUE);

		}
		else if(!BoardArray[i]->GetDeleteFlag())
		{
			DX11_MODEL model = pQuestBoard->GetPrefab()->GetModelDate();
			BoardArray[i]->GetPrefab()->SetModelDate(model);
		}

	}

	// ���킢�G�b�t�F�N�g
	m_EffectCnt++;
	if (m_EffectCnt == 100)
	{
		for (int i = 0; i < BoardArray.size(); i++)
		{
			if (BoardArray.empty()) return;

			if (BoardArray[i]->GetChangeModelFlag())
			{
				Lamp *pLamp = BoardArray[i]->GetLampManager()->GetLamp();

				XMFLOAT3 pos = pLamp[0].GetPos();

				pParticlManager->CallParticle(pos, 15.0f, i+1, EFFECT_NIGIWAI, MOVE_PATTERN_STOP, 8);

			}
		}

		m_EffectCnt = 0;
	}


	int count = 0;
	// �ό��q��������Ɣ����X�s�[�h�A�b�v
	for (int i = 0; i < BoardArray.size(); i++)
	{
		if (BoardArray[i]->GetChangeModelFlag())
		{
			count++;
		}
	}

	if (count > 3)
	{
		m_Speed = 200;
		m_MaxGarbageCnt = 8;
	}



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

	pParticlManager->Draw(0);
	m_pGarbageIcon->Draw();
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

void QuestBoardManager::Init()
{
	m_StartPos = { 0.0f ,0.0f,0.0f };
	m_MakeCnt = 0;		// �o���J�E���g
	m_failureCount = 0;
	m_MissionPoint = 0;
	BoardArray.clear();

}
