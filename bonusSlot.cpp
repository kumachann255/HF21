#include "bonusSlot.h"
#include "input.h"
#include "GodObject.h"

BonusSlot::BonusSlot()
{
	// ➑̂̏�����
	pHousing = new BonusHousing();

	// ➑̂̑傫���Z�b�g
	XMFLOAT3 sclHousing = { 1.0f,1.0f,1.0f };
	pHousing->GetPrefab()->SetScl(sclHousing);

	// ➑̂̌����Z�b�g
	XMFLOAT3 rotHousing = { 0.0f,3.14f,0.0f };
	pHousing->GetPrefab()->SetRot(rotHousing);

	// �h����3D�̏�����
	pDrumL = new BonusDrum();
	pDrumC = new BonusDrum();
	pDrumR = new BonusDrum();

	// �h����3D�̑傫���Z�b�g
	XMFLOAT3 scl = { 1.0f,1.0f,1.0f };
	pDrumL->GetPrefab()->SetScl(scl);
	pDrumC->GetPrefab()->SetScl(scl);
	pDrumR->GetPrefab()->SetScl(scl);

	// �h����3D�̃��[�J���ʒu�Z�b�g
	XMFLOAT3 posDrumL = { -5.0f,0.0f,0.0f };
	XMFLOAT3 posDrumC = { 0.0f,0.0f,0.0f };
	XMFLOAT3 posDrumR = { 5.0f,0.0f,0.0f };
	pDrumL->GetPrefab()->SetPos(posDrumL);
	pDrumC->GetPrefab()->SetPos(posDrumC);
	pDrumR->GetPrefab()->SetPos(posDrumR);

}

void BonusSlot::Update(void)
{

	pDrumL->Update();
	pDrumC->Update();
	pDrumR->Update();
	pHousing->Update();

	// ���Ԃ�i�߂�
	if (m_move)
	{
		m_count++;
	}

	// �~�߂�
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

			if ((pDrumR->GetColor() == pDrumC->GetColor()) &&
				(pDrumR->GetColor() == pDrumL->GetColor()))
			{
				pHousing->SetGoMorphing();
			}

			//m_shot = true;
		}
	}

	// ��
	if ((GetKeyboardTrigger(DIK_RETURN)))
	{
		pDrumR->SpinStart();
		if (!m_move) m_count = 0;
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

void BonusSlot::Draw()
{
	pDrumL->Draw();
	pDrumC->Draw();
	pDrumR->Draw();
	pHousing->Draw();
}


XMFLOAT4 BonusSlot::GetColor(void)
{
	XMFLOAT4 color = { 0.2f,0.2f,0.2f,1.0f };

	if (!pDrumL->GetMove())
	{
		if ((pDrumR->GetColor() == pDrumC->GetColor()) &&
			(pDrumR->GetColor() == pDrumL->GetColor()))
		{
			pHousing->SetGoMorphing();
		}



		//switch (pDrumR->GetColor())
		//{
		//case drum3D_red:
		//	color.x += 0.7f;
		//	break;

		//case drum3D_blue:
		//	color.z += 0.7f;
		//	break;

		//case drum3D_yellow:
		//	color.x += 0.35f;
		//	color.y += 0.35f;
		//	break;
		//}
	}

	//if (!pDrumC->GetMove())
	//{
	//	switch (pDrumC->GetColor())
	//	{
	//	case drum3D_red:
	//		color.x += 0.7f;
	//		break;

	//	case drum3D_blue:
	//		color.z += 0.7f;

	//		// �΂͓���
	//		if (pDrumR->GetColor() == drum3D_yellow)
	//		{
	//			color = { 0.2f,1.4f,0.2f,1.0f };
	//		}
	//		break;

	//	case drum3D_yellow:
	//		color.x += 0.35f;
	//		color.y += 0.35f;

	//		// �΂͓���
	//		if (pDrumR->GetColor() == drum3D_blue)
	//		{
	//			color = { 0.2f,1.4f,0.2f,1.0f };
	//		}
	//		break;
	//	}
	//}

	return color;
}
