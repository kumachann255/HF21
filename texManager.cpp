#include "texManager.h"
#include "GodObject.h"
#include "TrainingCrowManager.h"
TexManager::TexManager(God * god):GodObject(god)
{
	m_pUiManager = new UIManager();

	XMFLOAT3 pos0 = { 0.0f,0.0f,0.0f };
	XMFLOAT3 pos1 = { 480.0f,270.0f,0.0f };
	float w0 = 350.0f;
	float h0 = 100.0f;
	int time0 = 0;

	m_pUiManager->Register(new UIObject(pos0, 432.0f, 380.0f, time0));
	m_pUiManager->Register(new UIObject(pos1, 960, 540.0f, time0));

	m_pUiManager->Register(new UIObject(pos0, 600.0f, 200.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 700.0f, 200.0f, time0));

	m_pUiManager->Register(new UIObject(pos0, 300.0f, 350.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 300.0f, 350.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 300.0f, 350.0f, time0));

	m_pUiManager->Register(new UIObject(pos0, 300.0f, 37.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 300.0f, 75.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 300.0f, 75.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 300.0f, 75.0f, time0));

	m_pUiManager->Register(new UIObject(pos0, 600.0f, 120.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 500.0f, 200.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 600.0f, 140.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 450.0f, 50.0f, time0));

	m_pUiManager->Register(new UIObject(pos0, 960, 540.0f, time0));
	m_pUiManager->Register(new UIObject(pos0, 2700, 540.0f, time0));


	for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
	{
		m_pUiManager->GetUIObject(i)->GetUITexData()->Create(g_TexturName[i]);
	}

	m_pUiManager->GetUIObject(ui_waku_full)->SetTexType(texType_endless);
	m_pUiManager->GetUIObject(ui_waku_full)->SetTexNo(ui_waku_full);
}

void TexManager::Update()
{
	for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
	{
		m_pUiManager->GetUIObject(i)->Update();
	}

	if (GetGod()->GetTrainingCrowManager()->GetBonus())
	{
		m_pUiManager->GetUIObject(ui_waku_full)->SetUse(FALSE);
	}
	else m_pUiManager->GetUIObject(ui_waku_full)->SetUse(TRUE);

}

void TexManager::Draw()
{
	for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
	{
		m_pUiManager->GetUIObject(i)->Draw();
	}
}
