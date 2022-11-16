#pragma once
#include "main.h"
#include "object.h"
#include "housing.h"
#include "drum3D.h"
#include "GodObject.h"
#include "FlyingCrowManager.h"

class Slot:public GodObject
{
private:
	Housing* pHousing = nullptr;
	Drum3D* pDrumL = nullptr;
	Drum3D* pDrumC = nullptr;
	Drum3D* pDrumR = nullptr;


	bool m_shot = false;
	int m_count = 0;
	bool m_move = false;



public:
	Slot(God *god);
	~Slot();
	//Slot(Housing* Housing, Drum3D* DrumL, Drum3D* DrumC, Drum3D* DrumR) : 
	//	pHousing(Housing), pDrumL(DrumL), pDrumC(DrumC), pDrumR(DrumR) {}

	void SetHousing(Housing* Housing) { pHousing = Housing; }
	void SetDrumL(Drum3D* DrumL) { pDrumL = DrumL; }
	void SetDrumC(Drum3D* DrumC) { pDrumL = DrumC; }
	void SetDrumR(Drum3D* DrumR) { pDrumL = DrumR; }

	Housing* GetHousing(void) {	return pHousing; }
	Drum3D* GetDrumL(void) { return pDrumL; }
	Drum3D* GetDrumC(void) { return pDrumC; }
	Drum3D* GetDrumR(void) { return pDrumR; }

	void Update(void);
	void Draw(void);

	XMFLOAT4 GetColor(void);

	void SetShot(bool data) { m_shot = data; }
	bool GetShot(void) { return m_shot; }






};