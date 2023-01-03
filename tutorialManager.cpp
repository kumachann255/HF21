#include "tutorialManager.h"

TutorialManager::TutorialManager(God * god) :GodObject(god)
{


}

TutorialManager::~TutorialManager()
{
}

void TutorialManager::Update()
{
	// 時間を進める
	m_count++;

	if (m_count % TUTORIAL_TELOP_DISTANCE == 0)
	{
		GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			m_telopType, texType_cutIn_right, XMFLOAT3(560.0f, 450.0f, 0.0f), TUTORIAL_TELOP_DISTANCE);

		switch (m_telopType)
		{
		case tutorial_04:
			// 左空き
			break;

		case tutorial_06:
			// 観光客メーターへの矢印
			break;

		case tutorial_11:
			// 右下空き
			break;

		case tutorial_12:
			// ドラムの説明
			break;

		case tutorial_17:
			// 右上空き
			break;

		case tutorial_22:
			// 左空き＋カレンダー矢印
			break;

		case tutorial_23:
			// 空き無し
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
