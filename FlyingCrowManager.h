//=============================================================================
//
// カラース管理処理 [FlyingCrowManager.h]
// Author : 
//
//=============================================================================
#pragma once
#include "FlyingCrow.h"
#include "GodObject.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CROWS_MAX (50)


//*****************************************************************************
// クラス定義
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
	void FlyingCrowManager::SetCrows(XMFLOAT3 pos, XMFLOAT3 rot);
	void SetRainbowColor(int i);
};