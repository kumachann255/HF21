#include "texManager.h"
#include "GodObject.h"
#include "TrainingCrowManager.h"
TexManager::TexManager(God * god):GodObject(god)
{
	m_pUiManager = new UIManager();

	XMFLOAT3 pos0 = { 0.0f,0.0f,0.0f };
	float w0 = 350.0f;
	float h0 = 100.0f;
	int time0 = 0;

	m_pUiManager->Register(new UIObject(pos0, 432.0f, 380.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 960, 540.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 600.0f, 200.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 300.0f, 350.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 300.0f, 350.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 300.0f, 350.0f, time0));

	m_pUiManager->Register(new UIObject(pos0, 300.0f, 37.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 300.0f, 75.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 300.0f, 75.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 300.0f, 75.0f, time0));

	m_pUiManager->Register(new UIObject(pos0, 600.0f, 90.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 960, 540.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 2700, 540.0f, time0));


	for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
	{
		m_pUiManager->GetUIObject(i)->GetUITexData()->Create(g_TexturName[i]);
	}

}

void TexManager::Update()
{
	for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
	{
		m_pUiManager->GetUIObject(i)->Update();
	}
}

void TexManager::Draw()
{
	for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
	{
		if ((i == ui_waku_full) && (GetGod()->GetTrainingCrowManager()->GetBonus())) continue;
		m_pUiManager->GetUIObject(i)->Draw();
	}
}
