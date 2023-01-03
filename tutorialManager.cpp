#include "tutorialManager.h"

TutorialManager::TutorialManager(God * god) :GodObject(god)
{


}

TutorialManager::~TutorialManager()
{
}

void TutorialManager::Update()
{
	// ���Ԃ�i�߂�
	m_count++;

	if (m_count % TUTORIAL_TELOP_DISTANCE == 0)
	{
		GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			m_telopType, texType_cutIn_right, XMFLOAT3(560.0f, 450.0f, 0.0f), TUTORIAL_TELOP_DISTANCE);

		switch (m_telopType)
		{
		case tutorial_04:
			// ����
			break;

		case tutorial_06:
			// �ό��q���[�^�[�ւ̖��
			break;

		case tutorial_11:
			// �E����
			break;

		case tutorial_12:
			// �h�����̐���
			break;

		case tutorial_17:
			// �E���
			break;

		case tutorial_22:
			// ���󂫁{�J�����_�[���
			break;

		case tutorial_23:
			// �󂫖���
			break;
		}

		m_telopType++;
	}

}

void TutorialManager::Draw()
{
}

void TutorialManager::Init()
{
	m_count = 0;
	m_telopType = tutorial_00;
}
