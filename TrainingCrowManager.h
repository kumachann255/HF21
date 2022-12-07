#pragma once
#include "main.h"
#include "God.h"
#include "trainingCrow.h"
#include "trainingCrowBench.h"
#include "trainingCrowDumbbell.h"
#include "room.h"

#define BONUS_START_TIME		(60)

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

	Room *m_pRoom = nullptr;

	int m_Type = No_Bench;

	BOOL m_isBonus = FALSE;
	BOOL m_isSpeedUp = FALSE;
	BOOL m_isTrainingSuccess = FALSE;
	int m_count = 0;

	BOOL m_isSuccess = FALSE;
	BOOL m_isFalseTelop = FALSE;

	int m_stock = 0;

public:
	TrainingCrowManager(God *god);

	void Update();
	void Draw();

	void SetIsSpeedUp(BOOL data) { m_isSpeedUp = data; }
	BOOL GetIsSpeedUp(void) { return m_isSpeedUp; }

	BOOL GetBonus(void) { return m_isBonus; }
	void SetBonus(BOOL data) { m_isBonus = data; }
	void SetBonusStart(void) { m_isTrainingSuccess = TRUE; }

	BOOL GetSuccess(void) { return m_isSuccess; }
	void SetSuccess(BOOL data) { m_isSuccess = data; }
	
	BOOL UseStock(void);
	void AddStock(void) { m_stock++; };

	void SetTrainingTypeRandom(void) { m_Type = rand() % No_TrainingMax; };
	
	void SetFalseTelop(BOOL data) { m_isFalseTelop = data; };
	BOOL GetFalseTelop(void) { return m_isFalseTelop; };
};