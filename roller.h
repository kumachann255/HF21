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

class Roller :public Object
{

private:


public:
	Roller();
	~Roller();

	void Update(void) override;

	void Draw(void) override;

};

