//=============================================================================
//
// Sky処理 [Sky.h]
// Author : 柏村大地
//
//=============================================================================

#pragma once
#include "object.h"


class Sky :public Object
{
private:


public:
	Sky();
	~Sky();

	// メンバ関数
	 void Update (void) override;
	 void Draw (void) override;

};

