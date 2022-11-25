#pragma once
#include "main.h"
#include "object.h"
#include "GodObject.h"
#include "model.h"
#include "Morphing.h"

#define MAX_SQUAT_MOVE	(2)	

class TrainingCrowSquat : public Object, GodObject, Morphing
{
private:
	Prefab *m_prefab2;

	Morphing *m_pMorphing = nullptr;

public:
	TrainingCrowSquat(God *god) :GodObject(god) {
		m_MorphingTypeMax = MAX_SQUAT_MOVE;

		m_prefab = new Prefab;
		m_prefab->SetModelMorphing("model_barbellsquat_crow02.obj");

		m_prefab2 = new Prefab;
		m_prefab2->SetModel("model_barbellsquat_crow01.obj");

		m_Squat_Vertex = new MODEL[MAX_SQUAT_MOVE];

		// モーフィングするオブジェクトの読み込み
		m_pMorphing = new Morphing;
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


};