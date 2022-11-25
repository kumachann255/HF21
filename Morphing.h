#pragma once
#include "main.h"
#include "model.h"

class Morphing
{
private:
protected:
	MODEL *m_Squat_Vertex = nullptr;
	VERTEX_3D *m_pVertex = nullptr;
	int m_MorphingTypeMax = 0;
	int m_MorphingType = 0;
	float m_time = 0.0f;


public:
	void LoadModel(char *FileName, MODEL *Model);
};