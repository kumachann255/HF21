//=============================================================================
//
// �J���[�X�Ǘ����� [FlyingCrowManager.h]
// Author : 
//
//=============================================================================
#pragma once
#include "FlyingCrow.h"
#include "GodObject.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CROWS_MAX (100)


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class FlyingCrowManager :public GodObject
{

private:
	FlyingCrow *m_pFlyingCrow = nullptr;
	int m_targetNo[3] = { 0, 0, 0 };
	XMFLOAT3 m_noneTargetPos = { -50.0f, 200.0f, -100.0f };

public:
	FlyingCrowManager(God *god);
	~FlyingCrowManager();

	void Update(void);
	void Draw(void);
	void SetShotCrows(XMFLOAT4 color, int colorType, int num);
	void SetRainbowColor(int i);
};