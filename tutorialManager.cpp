#include "tutorialManager.h"
#include "fade.h"
#include "input.h"
#include "UIManager.h"
#include "sound.h"
#include "modeSelect.h"

TutorialManager::TutorialManager(God * god) :GodObject(god)
{
	m_pTutorialBG = new TutorialBG();

}

TutorialManager::~TutorialManager()
{
}

void TutorialManager::Update()
{
	// �X�L�b�v
	if (GetKeyboardTrigger(DIK_S))
	{
		SetFade(FADE_OUT, STAGE_01ID);
	}

	// ���Ԃ�i�߂�i�V�[���J�ڂ���܂Łj
	if(m_telopType <= tutorial_24 + 1) m_count++;

	// ���ԂɂȂ邩���փ{�^���������ꂽ���ł��̃e���b�v��
	if ((m_count == TUTORIAL_TELOP_DISTANCE) || (GetKeyboardTrigger(DIK_SPACE)))
//	if ((m_count == TUTORIAL_TELOP_DISTANCE))
		{
		// ���x��SetFade���s��Ȃ��悤�ɂ���
		if (m_telopType > tutorial_24 + 1) return;

		// �A���œ���Ȃ��悤�Ƀ��Z�b�g
		m_count = 0;

		// �V�[���J��
		if (m_telopType > tutorial_24)
		{
			SetFade(FADE_OUT, STAGE_01ID);
			StopSound(SOUND_LABEL_BGM_tutorial);
			m_telopType++;
			return;
		}

		GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			m_telopType, texType_cutIn_left, XMFLOAT3(600.0f, 400.0f, 0.0f), TUTORIAL_TELOP_DISTANCE / 60);
		PlaySound(SOUND_LABEL_SE_se_tutorial_telop);

		switch (m_telopType)
		{
		case tutorial_04:
			// ����
			m_pTutorialBG->SetTex(tutorial_full, FALSE);
			m_pTutorialBG->SetTex(tutorial_left, TRUE);
			break;

		case tutorial_06:
			// �ό��q���[�^�[�ւ̖��
			m_pTutorialBG->SetTex(tutorial_arrow_tension, TRUE);
			break;

		case tutorial_08:
			// �S�~�̉�����@
			m_pTutorialBG->SetTex(tutorial_left, FALSE);
			m_pTutorialBG->SetTex(tutorial_arrow_tension, FALSE);
			m_pTutorialBG->SetTex(tutorial_full, TRUE);
			m_pTutorialBG->SetTex(tutorial_garbage, TRUE);
			break;

		case tutorial_11:
			// �E����
			m_pTutorialBG->SetTex(tutorial_full, FALSE);
			m_pTutorialBG->SetTex(tutorial_garbage, FALSE);
			m_pTutorialBG->SetTex(tutorial_rightDoun, TRUE);
			break;

		case tutorial_12:
			// �X���b�g�̑���
			if (GetPlayerType())
			{	// �L�[�{�[�h
				m_pTutorialBG->SetTex(tutorial_slot, TRUE);
			}
			else
			{	// �p�b�h
				m_pTutorialBG->SetTex(tutorial_slot_pad, TRUE);
			}

			break;

		case tutorial_17:
			// �E���
			m_pTutorialBG->SetTex(tutorial_slot, FALSE);
			m_pTutorialBG->SetTex(tutorial_slot_pad, FALSE);
			m_pTutorialBG->SetTex(tutorial_rightDoun, FALSE);
			m_pTutorialBG->SetTex(tutorial_rightUp, TRUE);
			m_pTutorialBG->SetTex(tutorial_arrow_protein, TRUE);

			break;

		case tutorial_22:
			// ���󂫁{�J�����_�[���
			m_pTutorialBG->SetTex(tutorial_rightUp, FALSE);
			m_pTutorialBG->SetTex(tutorial_arrow_protein, FALSE);
			m_pTutorialBG->SetTex(tutorial_left, TRUE);
			m_pTutorialBG->SetTex(tutorial_arrow_calendar, TRUE);
			break;

		case tutorial_24:
			// �󂫖���
			m_pTutorialBG->SetTex(tutorial_arrow_calendar, FALSE);
			m_pTutorialBG->SetTex(tutorial_left, FALSE);
			m_pTutorialBG->SetTex(tutorial_full, TRUE);
			break;
		}

		m_telopType++;
	}
}

void TutorialManager::Draw()
{
	m_pTutorialBG->Draw();
}

void TutorialManager::Init()
{
	m_count = 0;
	m_telopType = tutorial_00;
	m_pTutorialBG->Init();
}
