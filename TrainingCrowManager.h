#pragma once
#include "main.h"
#include "God.h"
#include "trainingCrow.h"
#include "trainingCrowBench.h"
#include "trainingCrowDumbbell.h"

enum
{
	No_Squat,
	No_Bench,
	No_Dumbbell,
	No_TrainingMax,
};

class TrainingCrowManager : public GodObject
{
private:
	TrainingCrowSquat *m_pTrainingCrowSquat = nullptr;
	TrainingCrowBench *m_pTrainingCrowBench = nullptr;
	TrainingCrowDumbbell *m_pTrainingCrowDumbbell = nullptr;

	int m_Type = No_Bench;

	BOOL m_isBonus = FALSE;
	BOOL m_isSpeedUp = FALSE;

public:
	TrainingCrowManager(God *god);

	void Update();
	void Draw();

	void SetIsSpeedUp(BOOL data) { m_isSpeedUp = data; }
	BOOL GetIsSpeedUp(void) { return m_isSpeedUp; }

	BOOL GetBonus(void) { return m_isBonus; }
};