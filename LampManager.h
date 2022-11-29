//=============================================================================
//
// �����v�}�l�[�W���[���� [LampManager.h]
// Author : 
//
//=============================================================================
#pragma once
#include "Lamp.h"
#include "GodObject.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LAMP_MAX	(3)


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class LampManager
{

private:
	Lamp m_lamps[LAMP_MAX] ;
	ID3D11ShaderResourceView	*m_Texture[LAMP_TYPE_MAX] = { nullptr };
	int m_swich = 0;
	float m_time = 0;
	XMFLOAT4 m_color = { 1.0f,1.0f,1.0f,1.0f };
public:
	LampManager();
	~LampManager();

	void Update(void);
	void Draw(XMMATRIX WorldMatrix);
	Lamp *GetLamp(void) { return &m_lamps[0]; }
	
};
