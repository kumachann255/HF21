#pragma once
#include "main.h"
#include "object.h"

class Housing : public Object
{
private:


public:
	Housing();
	~Housing() { delete m_prefab; };


};