#pragma once
#include "main.h"
#include "object.h"
#include "GodObject.h"

class Room : public Object, GodObject
{
private:


public:
	Room(God *god) :GodObject(god) {
		m_prefab = new Prefab;
		m_prefab->SetModel("model_room_temp.obj");

		XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
		XMFLOAT3 rot = { 0.0f, 3.14f *  0.75f, 0.0f };
		XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };

		SetPos(pos);
		SetRot(rot);
		SetScl(scl);

	}

	~Room() { delete m_prefab; };


};