#include "UIManager.h"
#include "texManager.h"


UIManager::UIManager()
{


}

UIManager::~UIManager()
{
	for (int i = 0; i < m_texNum; i++)
	{
		delete m_pUIObject[i];
	}
}

void UIManager::Update(void)
{
	for (int i=0; i < m_texNum; i++)
	{
		m_pUIObject[i]->Update();
	}

}

void UIManager::Draw(void)
{
	for (int i=0; i < m_texNum; i++)
	{
		m_pUIObject[i]->Draw();
	}

}

void UIManager::SetTexture(int texNo, int texType, XMFLOAT3 pos, int time)
{
	if (m_pUIObject[texNo]->GetUse()) return;
	m_pUIObject[texNo]->SetUse(TRUE);
	m_pUIObject[texNo]->SetPos(pos);
	m_pUIObject[texNo]->SetTexNo(texNo);
	m_pUIObject[texNo]->SetTexType(texType);
	m_pUIObject[texNo]->SetTime(time * 60);
	m_pUIObject[texNo]->ResetTex();
}
