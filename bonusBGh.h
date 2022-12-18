#pragma once
#include "main.h"
#include "object.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"

class BonusBG : public Object
{
private:

public:
	BonusBG();
	~BonusBG() { delete m_prefab; };

	void Update();
};