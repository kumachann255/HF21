#include "endingSun.h"

void EndingSun::Update()
{
	XMFLOAT3 rot = GetRot();
	rot.z += ENDING_SUM_LEN;
	SetRot(rot);

}
