#pragma once
#include "main.h"
#include "GodObject.h"
#include "texManager.h"
#include "tutorialBG.h"

#define TUTORIAL_TELOP_DISTANCE		(360)
class TutorialManager : public GodObject
{
private:
	int m_count = 0;
	int m_telopType = tutorial_00;

	TutorialBG *m_pTutorialBG = nullptr;


public:
	TutorialManager(God *god);
	~TutorialManager();

	void Update();
	void Draw();

	void Init();
};
