#include "FlyingCrow.h"

#define FLYINGSPEED		(0.01f)

void FlyingCrow::Update(void)
{
	this->m_time += this->GetSpeed();
	XMFLOAT3 pos;

	pos.x = ((1.0f - this->m_time) * (1.0f - this->m_time)*(1.0f - this->m_time)) * this->m_startPos.x
		+ (3.0f * ((1.0f - this->m_time) * (1.0f - this->m_time)) * this->m_time) * this->m_controlPosA.x
		+ 3.0f * ((1.0f - this->m_time) * (this->m_time * this->m_time)) * this->m_controlPosB.x
		+ (this->m_time * this->m_time * this->m_time) * m_targetPos.x;

	pos.y = ((1.0f - this->m_time) * (1.0f - this->m_time)*(1.0f - this->m_time)) * this->m_startPos.y
		+ (3.0f * ((1.0f - this->m_time) * (1.0f - this->m_time)) * this->m_time) * this->m_controlPosA.y
		+ 3.0f * ((1.0f - this->m_time) * (this->m_time * this->m_time)) * this->m_controlPosB.y
		+ (this->m_time * this->m_time * this->m_time) * m_targetPos.y;

	pos.z = ((1.0f - this->m_time) * (1.0f - this->m_time)*(1.0f - this->m_time)) * this->m_startPos.z
		+ (3.0f * ((1.0f - this->m_time) * (1.0f - this->m_time)) * this->m_time) * this->m_controlPosA.z
		+ 3.0f * ((1.0f - this->m_time) * (this->m_time * this->m_time)) * this->m_controlPosB.z
		+ (this->m_time * this->m_time * this->m_time) * m_targetPos.z;

	this->SetPos(pos);

	if (this->m_time >= 1.0f)
	{
		this->DeleteFlyingCrow();
	}

	if (this->GetScl().x > MAX_FLYINGCROW_SCL)
	{
		XMFLOAT3 scl = this->GetScl();
		scl.x -= VALUE_FLYINGCROW_SCL;
		scl.y -= VALUE_FLYINGCROW_SCL;
		scl.z -= VALUE_FLYINGCROW_SCL;
		this->SetScl(scl);
	}

}
