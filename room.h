#pragma once
#include "main.h"
#include "object.h"
#include "GodObject.h"
#include "prefab.h"


class Room : public Object
{
private:
	//Prefab *m_

public:
	Room();

	~Room() { delete m_prefab; };

	//void Update();

};