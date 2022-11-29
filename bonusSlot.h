#pragma once
#include "main.h"
#include "object.h"
#include "slot.h"
#include "bonusDrumh.h"

class BonusSlot
{
private:
	BonusHousing* pHousing = nullptr;
	BonusDrum* pDrumL = nullptr;
	BonusDrum* pDrumC = nullptr;
	BonusDrum* pDrumR = nullptr;

	bool m_shot = false;
	int m_count = 0;
	bool m_move = false;

public:
	BonusSlot();
	void SetHousing(BonusHousing* Housing) { pHousing = Housing; }
	void SetDrumL(BonusDrum* DrumL) { pDrumL = DrumL; }
	void SetDrumC(BonusDrum* DrumC) { pDrumC = DrumC; }
	void SetDrumR(BonusDrum* DrumR) { pDrumR = DrumR; }

	BonusHousing* GetHousing(void) { return pHousing; }
	BonusDrum* GetDrumL(void) { return pDrumL; }
	BonusDrum* GetDrumC(void) { return pDrumC; }
	BonusDrum* GetDrumR(void) { return pDrumR; }

	void BonusSlot::Update(void);
	void BonusSlot::Draw();
	XMFLOAT4 BonusSlot::GetColor(void);

	void SetShot(bool data) { m_shot = data; }
	bool GetShot(void) { return m_shot; }



};
