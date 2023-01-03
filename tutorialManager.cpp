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
	// スキップ
	if (GetKeyboardTrigger(DIK_S))
	{
		SetFade(FADE_OUT, STAGE_01ID);
	}

	// 時間を進める（シーン遷移するまで）
	if(m_telopType <= tutorial_24 + 1) m_count++;

	// 時間になるか次へボタンが押されたかでつぎのテロップへ
	if ((m_count == TUTORIAL_TELOP_DISTANCE) || (GetKeyboardTrigger(DIK_SPACE)))
//	if ((m_count == TUTORIAL_TELOP_DISTANCE))
		{
		// 何度もSetFadeを行わないようにする
		if (m_telopType > tutorial_24 + 1) return;

		// 連続で入らないようにリセット
		m_count = 0;

		// シーン遷移
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
			// 左空き
			m_pTutorialBG->SetTex(tutorial_full, FALSE);
			m_pTutorialBG->SetTex(tutorial_left, TRUE);
			break;

		case tutorial_06:
			// 観光客メーターへの矢印
			m_pTutorialBG->SetTex(tutorial_arrow_tension, TRUE);
			break;

		case tutorial_08:
			// ゴミの回収方法
			m_pTutorialBG->SetTex(tutorial_left, FALSE);
			m_pTutorialBG->SetTex(tutorial_arrow_tension, FALSE);
			m_pTutorialBG->SetTex(tutorial_full, TRUE);
			m_pTutorialBG->SetTex(tutorial_garbage, TRUE);
			break;

		case tutorial_11:
			// 右下空き
			m_pTutorialBG->SetTex(tutorial_full, FALSE);
			m_pTutorialBG->SetTex(tutorial_garbage, FALSE);
			m_pTutorialBG->SetTex(tutorial_rightDoun, TRUE);
			break;

		case tutorial_12:
			// スロットの操作
			if (GetPlayerType())
			{	// キーボード
				m_pTutorialBG->SetTex(tutorial_slot, TRUE);
			}
			else
			{	// パッド
				m_pTutorialBG->SetTex(tutorial_slot_pad, TRUE);
			}

			break;

		case tutorial_17:
			// 右上空き
			m_pTutorialBG->SetTex(tutorial_slot, FALSE);
			m_pTutorialBG->SetTex(tutorial_slot_pad, FALSE);
			m_pTutorialBG->SetTex(tutorial_rightDoun, FALSE);
			m_pTutorialBG->SetTex(tutorial_rightUp, TRUE);
			m_pTutorialBG->SetTex(tutorial_arrow_protein, TRUE);

			break;

		case tutorial_22:
			// 左空き＋カレンダー矢印
			m_pTutorialBG->SetTex(tutorial_rightUp, FALSE);
			m_pTutorialBG->SetTex(tutorial_arrow_protein, FALSE);
			m_pTutorialBG->SetTex(tutorial_left, TRUE);
			m_pTutorialBG->SetTex(tutorial_arrow_calendar, TRUE);
			break;

		case tutorial_24:
			// 空き無し
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
