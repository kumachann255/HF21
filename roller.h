//=============================================================================
//
// ���[���[���� [roller.h]
// Author : ������n
//
//=============================================================================

#pragma once
#include "object.h"
#include "GodObject.h"

class Roller :public Object , GodObject
{

private:


public:
	Roller(God *god);
	~Roller();

	void Update(void) override;

	//void Draw(void) override;

};
