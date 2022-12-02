#pragma once
#include "main.h"
#include "GodObject.h"
#include "endingStage.h"
#include "endingSun.h"

class AnimationManager : public GodObject
{
private:
	EndingStage *m_pEndingStage = nullptr;
	EndingSun *m_pEndingSun = nullptr;

public:
	AnimationManager(God *god);

	void Update(void);
	void Draw(void);



};