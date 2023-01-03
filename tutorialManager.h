#pragma once
#include "main.h"
#include "GodObject.h"
#include "texManager.h"

#define TUTORIAL_TELOP_DISTANCE		(180)
class TutorialManager : public GodObject
{
private:
	int m_count = 0;
	int m_telopType = tutorial_00;

public:
	TutorialManager(God *god);
	~TutorialManager();

	void Update();
	void Draw();

	void Init();
};
