#pragma once
#include "main.h"
#include "object.h"
#include "GodObject.h"
#include "model.h"
#include "Morphing.h"
#include "prefab.h"

#define MAX_DUMBBELL_MOVE	(2)	
#define DUMBBELL_SPEED		(0.015f)
#define MAX_DUMBBELL_SPEED	(0.7f)
#define ADD_DUMBBELL_SPEED	(0.0015f)
#define DUMBBELL_MAX_ROT	(1.0f)

#define MAX_DUMBBELL_MAXSPEED_TIME	(80)

#define DUMBBELL_Y_OFFSET	(2.0f)

class TrainingCrowDumbbell : public Object, GodObject
{
private:
	Prefab *m_prefabBench;
	Prefab *m_prefabWing;

	XMFLOAT3 m_wing_Pos;
	XMFLOAT3 m_wing_Rot;

	float m_vec = 1.0f;
	float m_speed = DUMBBELL_SPEED;
	int m_count = 0;
	BOOL m_isUp = FALSE;
	int m_waitCount = 0;


public:
	TrainingCrowDumbbell(God *god) :GodObject(god) {

		m_prefab = new Prefab;
		m_prefab->SetModelMorphing("model_dumbbell_crowbody.obj");

		m_prefabBench = new Prefab;
		m_prefabBench->SetModel("model_bench.obj");

		m_prefabWing = new Prefab;
		m_prefabWing->SetModel("model_dumbbell_wing.obj");

		XMFLOAT3 pos = m_wing_Pos = { 0.0f, -30.0f, 0.0f };
		XMFLOAT3 rot = m_wing_Rot = { 0.0f, 3.14f *  0.75f, 0.0f };
		XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };

		m_wing_Pos.x = 2.0f;
		m_wing_Pos.y = 4.5f;
		m_wing_Pos.z = 8.0f;
		m_wing_Rot.z = -0.5f;

		SetPos(pos);
		SetRot(rot);
		SetScl(scl);

	}

	void Update();
	void Draw();

	~TrainingCrowDumbbell() { delete m_prefab; };


};