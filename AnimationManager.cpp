#include "AnimationManager.h"
#include "endingStage.h"

AnimationManager::AnimationManager(God * god) :GodObject(god)
{
	m_pEndingStage = new EndingStage();
	m_pEndingSun = new EndingSun();


}

void AnimationManager::Update(void)
{
	m_pEndingStage->Update();
	m_pEndingSun->Update();
}

void AnimationManager::Draw(void)
{
	m_pEndingStage->Draw();

}
