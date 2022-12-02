#include "UIManager.h"



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
