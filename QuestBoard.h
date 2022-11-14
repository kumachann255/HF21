//=============================================================================
//
// クエストボード処理 [QuestBoard.h]
// Author : 柏村大地
//
//=============================================================================
#pragma once
#include "object.h"


class QuestBoard : public Object
{
private:
	float m_time = 0.0f;
	XMFLOAT3 m_pos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 m_rot = { 0.0f, 0.0f, 0.0f };

public:
	QuestBoard() {}
	QuestBoard(const std::string name , const XMFLOAT3 pos);
	~QuestBoard();

	// メンバ関数
	void Update(void) override;
	void Draw(XMMATRIX WorldMatrix);


};
