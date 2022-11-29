#pragma once
#include "main.h"
#include "object.h"
#include "drum3D.h"

enum {
	Bonusdrum3D_red,
	Bonusdrum3D_yellow,
	Bonusdrum3D_green,
	Bonusdrum3D_blue,
	Bonusdrum3D_purple,
	Bonusdrum3D_max,
};


class BonusDrum : public Drum3D
{
private:

public:
	BonusDrum();

	~BonusDrum() { delete m_prefab; };
};