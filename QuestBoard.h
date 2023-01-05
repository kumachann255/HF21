//=============================================================================
//
// クエストボード処理 [QuestBoard.h]
// Author : 柏村大地
//
//=============================================================================
#pragma once
#include "object.h"
#include "LampManager.h"

class QuestBoard : public Object
{
private:
	LampManager *pLampManager = nullptr;
	float m_time = 0.0f;
	XMFLOAT3 m_pos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 m_rot = { 0.0f, 0.0f, 0.0f };
	BOOL m_DeleteFlag = FALSE;
	BOOL m_ChangeModelFlag = FALSE;

public:
	QuestBoard(XMFLOAT3 pos, XMFLOAT3 rot);
	QuestBoard(const std::string name, const XMFLOAT3 pos, const XMFLOAT3 rot);
	~QuestBoard();

	// メンバ関数
	void Update(void) override;
	void Draw(XMMATRIX WorldMatrix);
	LampManager *GetLampManager() { return pLampManager; }
	BOOL GetDeleteFlag(void) { return m_DeleteFlag; }
	void SetDeleteFlag(BOOL flag) {  m_DeleteFlag = flag; }
	BOOL GetChangeModelFlag(void) { return m_ChangeModelFlag; }
	void SetChangeModelFlag(BOOL flag) { m_ChangeModelFlag = flag; }

};
