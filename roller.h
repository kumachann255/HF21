//=============================================================================
//
// ���[���[���� [roller.h]
// Author : ������n
//
//=============================================================================

#pragma once
#include "object.h"
#include "GodObject.h"

#define	ROTATE_SPEED		(0.001f)		// ��]���x

class Roller :public Object , GodObject
{

private:


public:
	Roller(God *god);
	~Roller();

	void Update(void) override;

	//void Draw(void) override;

};
