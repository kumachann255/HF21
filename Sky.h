//=============================================================================
//
// Sky���� [Sky.h]
// Author : ������n
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

	// �����o�֐�
	 void Update (void) override;
	 void Draw (void) override;

};

