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
public:
	FlyingCrowManager(God *god);
	~FlyingCrowManager();

	void Update(void);
	void Draw(void);
	void SetShotCrows(XMFLOAT4 color);
	void FlyingCrowManager::SetCrows(XMFLOAT3 pos, XMFLOAT3 rot);

};
