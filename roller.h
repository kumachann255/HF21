//=============================================================================
//
// ローラー処理 [roller.h]
// Author : 柏村大地
//
//=============================================================================

#pragma once
#include "object.h"

class Roller :public Object
{

private:


public:
	Roller();
	~Roller();

	void Update(void) override;

	//void Draw(void) override;

};
