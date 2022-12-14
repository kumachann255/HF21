//=============================================================================
//
// ランプ処理 [Lamp.h]
// Author : 柏村大地
//
//=============================================================================

#pragma once
#include "object.h"


enum LAMP_TYPE
{
	LAMP_TYPE_RED,
	LAMP_TYPE_BLUE,
	LAMP_TYPE_GREEN,
	LAMP_TYPE_YELLOW,
	LAMP_TYPE_PINK,
	LAMP_TYPE_PURPLE,
	LAMP_TYPE_ORANGE,
	LAMP_TYPE_MAX,
	LAMP_TYPE_NONE,

};


class Lamp :public Object
{
private:
	int m_ColorTypeId = 0;
	BOOL m_clear = FALSE;
	int m_count = 0;

public:
	Lamp();
	~Lamp();

	// メンバ関数
	 void Update (void) override;
	 void Draw(XMMATRIX WorldMatrix);
	 int GetColorTypeId(void) { return m_ColorTypeId; }
	 void SetColorTypeId(int colorId) {  m_ColorTypeId = colorId; }

	 void SetDelete(BOOL data) { m_clear = data; };
	 BOOL GetDelete(void) { return m_clear; };
};

