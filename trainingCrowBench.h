#pragma once
#include "main.h"
#include "object.h"
#include "GodObject.h"
#include "model.h"
#include "Morphing.h"

#define MAX_BENCH_MOVE	(2)	
#define BENCH_SPEED		(1.0f)
#define BENCH_MAX_HEIGHT	(30.0f)

#define BENCH_Y_OFFSET	(2.0f)

class TrainingCrowBench : public Object, GodObject
{
private:
	Prefab *m_prefabBench;
	Prefab *m_prefabWing;
	Prefab *m_prefabbarbell;

	XMFLOAT3 m_wing_Pos;
	XMFLOAT3 m_barbell_Pos;

	float m_vec = 1.0f;

public:
	TrainingCrowBench(God *god) :GodObject(god) {

		m_prefab = new Prefab;
		m_prefab->SetModelMorphing("model_benchpress_crowbody.obj");

		m_prefabBench = new Prefab;
		m_prefabBench->SetModel("model_bench.obj");

		m_prefabWing = new Prefab;
		m_prefabWing->SetModel("model_benchpress_crowwing.obj");

		m_prefabbarbell = new Prefab;
		m_prefabbarbell->SetModel("model_benchpress_barbell.obj");

		XMFLOAT3 pos = m_wing_Pos = m_barbell_Pos = { 0.0f, -30.0f, 0.0f };
		XMFLOAT3 rot = { 0.0f, 3.14f *  0.75f, 0.0f };
		XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };

		SetPos(pos);
		SetRot(rot);
		SetScl(scl);

	}

	void Update();
	void Draw();

	~TrainingCrowBench() { delete m_prefab; };


};