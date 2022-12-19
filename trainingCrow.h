#pragma once
#include "main.h"
#include "object.h"
#include "GodObject.h"
#include "model.h"
#include "Morphing.h"

#define MAX_SQUAT_MOVE	(2)	
#define MAX_SQUAT_SPEED	(0.3f)
#define MIN_SQUAT_SPEED	(0.02f)
#define ADD_SQUAT_SPEED	(0.001f)

#define MAX_SQUAT_MAXSPEED_TIME	(80)
#define WAIT_SQUAT_TIME	(60)

class TrainingCrowSquat : public Object, GodObject, Morphing
{
private:
	float m_speed = 0.03f;
	BOOL m_isSpeedUp = FALSE;
	int m_count = 0;

	int m_waitCount = 0;

public:
	TrainingCrowSquat(God *god) :GodObject(god) {
		m_MorphingTypeMax = MAX_SQUAT_MOVE;

		m_prefab = new Prefab;
		m_prefab->SetModelMorphing("model_barbellsquat_crow02.obj");

		m_Squat_Vertex = new MODEL[MAX_SQUAT_MOVE];

		// モーフィングするオブジェクトの読み込み
		LoadObj("data/MODEL/model_barbellsquat_crow01.obj", &m_Squat_Vertex[0]);
		LoadObj("data/MODEL/model_barbellsquat_crow02.obj", &m_Squat_Vertex[1]);

		// 中身を配列として使用できるように仕様変更
		m_pVertex = new VERTEX_3D[m_Squat_Vertex[0].VertexNum];

		// 差分(途中経過)の初期化
		for (int i = 0; i < m_Squat_Vertex[0].VertexNum; i++)
		{
			m_pVertex[i].Position = m_Squat_Vertex[0].VertexArray[i].Position;
			m_pVertex[i].Diffuse = m_Squat_Vertex[0].VertexArray[i].Diffuse;
			m_pVertex[i].Normal = m_Squat_Vertex[0].VertexArray[i].Normal;
			m_pVertex[i].TexCoord = m_Squat_Vertex[0].VertexArray[i].TexCoord;
		}


		XMFLOAT3 pos = { 0.0f, -30.0f, 0.0f };
		XMFLOAT3 rot = { 0.0f, 3.14f *  0.75f, 0.0f };
		XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };

		SetPos(pos);
		SetRot(rot);
		SetScl(scl);

	}

	void Update();

	~TrainingCrowSquat() { delete m_prefab; };

	void Init();
};