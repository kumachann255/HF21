//=============================================================================
//
// ローラー処理 [roller.h]
// Author : 柏村大地
//
//=============================================================================

#pragma once
#include "object.h"
#include "GodObject.h"

#define	ROTATE_SPEED		(0.001f)		// 回転速度

class Roller :public Object
{

private:


public:
	Roller();
	~Roller();

	void Update(void) override;

	void Draw(void) override;

};

