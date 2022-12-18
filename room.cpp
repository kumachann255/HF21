#include "room.h"
#include "camera.h"

Room::Room()
{
	m_prefab = new Prefab;
	m_prefab->SetModel("model_trainingroom_item02.obj");
	//m_prefab->SetModel("cone.obj");
	
	XMFLOAT3 pos = { 0.0f, -100.0f, 0.0f };
	XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 scl = { 12.0f, 12.0f, 12.0f };

	SetPos(pos);
	SetRot(rot);
	SetScl(scl);

}

//void Room::Update()
//{
//	CAMERA *camera = GetCameraEvent();
//
//
//
//}
