#pragma once
#include "UI.h"

#define UITEX_MAX	(62)


class UIManager
{
private:
	UIObject *m_pUIObject[UITEX_MAX] = { nullptr };
	int m_texNum = 0;
public:
	UIManager();
	~UIManager();

	void Update(void);
	void Draw(void);
	UIObject *GetUIObject(void) {return m_pUIObject[0];}

	void Register(UIObject *pUIObject) {

		m_pUIObject[m_texNum] = pUIObject;
		m_texNum++;
	}

	UIObject* GetUIObject(int index) {

		return m_pUIObject[index];
	}

	void SetTexture(int texNo, int texType, XMFLOAT3 pos, int time);

};

