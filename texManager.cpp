#include "texManager.h"
#include "GodObject.h"
#include "TrainingCrowManager.h"
#include "slotManager.h"
#include "input.h"

TexManager::TexManager(God * god):GodObject(god)
{
	m_pUiManager = new UIManager();

	XMFLOAT3 pos0 = { 0.0f,0.0f,0.0f };
	XMFLOAT3 pos1 = { 480.0f,270.0f,0.0f };
	float w0 = 350.0f;
	float h0 = 100.0f;
	int time0 = 0;

	m_pUiManager->Register(new UIObject(pos1, 1300.0f, 1300.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 1300.0f, 1300.0f, time0));

	m_pUiManager->Register(new UIObject(pos1, 960, 540.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 960, 540.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 960, 540.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 960, 540.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 960, 540.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 960, 540.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 960, 540.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 960, 540.0f, time0));

	m_pUiManager->Register(new UIObject(pos0, 600.0f, 200.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 700.0f, 200.0f, time0));

	m_pUiManager->Register(new UIObject(pos0, 200.0f, 300.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 200.0f, 300.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 200.0f, 300.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 450.0f, 80.0f, time0));

	m_pUiManager->Register(new UIObject(pos0, 300.0f, 37.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 300.0f, 75.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 300.0f, 75.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 300.0f, 75.0f, time0));

	m_pUiManager->Register(new UIObject(pos0, 600.0f, 120.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 600.0f, 300.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 500.0f, 200.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 600.0f, 140.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 450.0f, 50.0f, time0));

	m_pUiManager->Register(new UIObject(pos0, 500.0f, 90.0f, time0));

	m_pUiManager->Register(new UIObject(pos0, 432.0f, 380.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 960.0f, 540.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 2700.0f, 540.0f, time0));

	m_pUiManager->Register(new UIObject(pos1, 960.0f, 540.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 960.0f, 540.0f, time0));

	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 660.0f, 130.0f, time0));

	m_pUiManager->Register(new UIObject(pos1, 580.0f, 150.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 580.0f, 150.0f, time0));

	for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
	{
		m_pUiManager->GetUIObject(i)->GetUITexData()->Create(g_TexturName[i]);
	}

	m_pUiManager->GetUIObject(m_wakuType)->SetTexType(texType_endless);

}

void TexManager::Update()
{
	for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
	{
		m_pUiManager->GetUIObject(i)->Update();
	}

	// 一旦すべての枠をFALSEに
	for (int i = ui_waku_full_spring; i <= ui_waku_full_winter; i++)
	{
		m_pUiManager->GetUIObject(i)->SetUse(FALSE);
	}

	// 今表示したい枠だけTRUEに
	if (GetGod()->GetTrainingCrowManager()->GetBonus())
	{
		m_pUiManager->GetUIObject(m_wakuType)->SetUse(FALSE);
	}
	else if (GetGod()->GetSlotManager()->GetRainbow())
	{
		m_pUiManager->GetUIObject(m_wakuType + 1)->SetUse(TRUE);
	}
	else m_pUiManager->GetUIObject(m_wakuType)->SetUse(TRUE);

#ifdef _DEBUG	// デバッグ情報を表示する

	if (GetKeyboardTrigger(DIK_W))
	{
		m_wakuType++;
		if (m_wakuType > ui_waku_full_winter) m_wakuType = ui_waku_full_spring;
	}
#endif
}

void TexManager::Draw()
{
	for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
	{
		m_pUiManager->GetUIObject(i)->Draw();
	}
}

void TexManager::Init(int type)
{
	m_wakuType = type;
	for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
	{
		m_pUiManager->GetUIObject(i)->SetUse(FALSE);
	}
}
