#include "slot.h"
#include "input.h"

enum {
	drum3D_red,
	drum3D_blue,
	drum3D_yellow,
};

#define SLOT_SIZE	(1.0f)


Slot::Slot(God *god) :GodObject(god)
{

	// 筐体の初期化
	pHousing = new Housing();

	// 筐体の大きさセット
	XMFLOAT3 sclHousing = { 1.0f,1.0f,1.0f };
	pHousing->GetPrefab()->SetScl(sclHousing);

	// 筐体の向きセット
	XMFLOAT3 rotHousing = { 0.0f,3.14f,0.0f };
	pHousing->GetPrefab()->SetRot(rotHousing);

	// ドラム3Dの初期化
	pDrumL = new Drum3D();
	pDrumC = new Drum3D();
	pDrumR = new Drum3D();

	// ドラム3Dの大きさセット
	XMFLOAT3 scl = { 1.0f,1.0f,1.0f };
	pDrumL->GetPrefab()->SetScl(scl);
	pDrumC->GetPrefab()->SetScl(scl);
	pDrumR->GetPrefab()->SetScl(scl);

	// ドラム3Dのローカル位置セット
	XMFLOAT3 posDrumL = { -5.0f,0.0f,0.0f };
	XMFLOAT3 posDrumC = { 0.0f,0.0f,0.0f };
	XMFLOAT3 posDrumR = { 5.0f,0.0f,0.0f };
	pDrumL->GetPrefab()->SetPos(posDrumL);
	pDrumC->GetPrefab()->SetPos(posDrumC);
	pDrumR->GetPrefab()->SetPos(posDrumR);

}

Slot::~Slot()
{
	delete pDrumL;
	delete pDrumC;
	delete pDrumR;
	delete pHousing;
}


void Slot::Update(void)
{

	pDrumL->Update();
	pDrumC->Update();
	pDrumR->Update();


	// 時間を進める
	if (m_move)
	{
		m_count++;
	}

	// 止める
	if ((GetKeyboardTrigger(DIK_SPACE)) && (m_count > 40))
	{
		if (pDrumR->GetMove())
		{
			pDrumR->Stop();
			m_move = false;
		}
		else if (pDrumC->GetMove())
		{
			pDrumC->Stop();
		}
		else if (pDrumL->GetMove())
		{
			pDrumL->Stop();
			m_shot = true;
		}
	}

	// 回す
	if ((GetKeyboardTrigger(DIK_RETURN)))
	{
		pDrumR->SpinStart();
		if(!m_move) m_count = 0;
		m_move = true;
	}

	if (m_move)
	{
		if ((m_count > 20) && (!pDrumC->GetMove()))
		{
			pDrumC->SpinStart();
		}
		else if ((m_count > 40) && (!pDrumL->GetMove()))
		{
			pDrumL->SpinStart();
		}
	}
}

void Slot::Draw()
{
	pDrumL->Draw();
	pDrumC->Draw();
	pDrumR->Draw();
	pHousing->Draw();
}


XMFLOAT4 Slot::GetColor(void)
{
	XMFLOAT4 color = { 0.2f,0.2f,0.2f,1.0f };

	if (!pDrumR->GetMove())
	{
		switch (pDrumR->GetColor())
		{
		case drum3D_red:
			color.x += 0.7f;
			break;

		case drum3D_blue:
			color.z += 0.7f;
			break;

		case drum3D_yellow:
			color.x += 0.35f;
			color.y += 0.35f;
			break;
		}
	}

	if (!pDrumC->GetMove())
	{
		switch (pDrumC->GetColor())
		{
		case drum3D_red:
			color.x += 0.7f;
			break;

		case drum3D_blue:
			color.z += 0.7f;

			// 緑は特殊
			if (pDrumR->GetColor() == drum3D_yellow)
			{
				color = { 0.2f,1.4f,0.2f,1.0f };
			}
			break;

		case drum3D_yellow:
			color.x += 0.35f;
			color.y += 0.35f;

			// 緑は特殊
			if (pDrumR->GetColor() == drum3D_blue)
			{
				color = { 0.2f,1.4f,0.2f,1.0f };
			}
			break;
		}
	}

	return color;
}
