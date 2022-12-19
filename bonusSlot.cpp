#include "bonusSlot.h"
#include "input.h"
#include "GodObject.h"
#include "sound.h"

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

			PlaySound(SOUND_LABEL_SE_se_slot_stop_bonus);
		}
		else if (pDrumC->GetMove())
		{
			pDrumC->Stop();
			PlaySound(SOUND_LABEL_SE_se_slot_stop_bonus);
		}
		else if (pDrumL->GetMove())
		{
			pDrumL->Stop();

			if ((pDrumR->GetColor() == pDrumC->GetColor()) &&
				(pDrumR->GetColor() == pDrumL->GetColor()))
			{
				pHousing->SetGoMorphing();

				switch (pDrumR->GetColor())
				{
				case bonus_drum3D_red:
					pHousing->SetColor(XMFLOAT4(1.0f, 0.282f, 0.333f, 1.0f));
					break;

				case bonus_drum3D_blue:
					pHousing->SetColor(XMFLOAT4(0.0f, 0.282f, 0.666f, 1.0f));
					break;

				case bonus_drum3D_yellow:
					pHousing->SetColor(XMFLOAT4(0.854f, 0.854f, 0.2f, 1.0f));
					break;

				case bonus_drum3D_green:
					pHousing->SetColor(XMFLOAT4(0.427f, 0.713f, 0.0f, 1.0f));
					break;

				case bonus_drum3D_purple:
					pHousing->SetColor(XMFLOAT4(0.427f, 0.427f, 0.666f, 1.0f));
					break;

				}
			}

			PlaySound(SOUND_LABEL_SE_se_slot_stop_bonus);
		}
	}

	// ��
	if ((GetKeyboardTrigger(DIK_RETURN)) && (pHousing->GetResultNum() < 3))
	{
		pDrumR->SpinStart();
		if (!m_move) m_count = 0;
		m_move = true;
		PlaySound(SOUND_LABEL_SE_se_slot_lever_bonus);
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

void BonusSlot::Init()
{
	m_shot = false;
	m_count = 0;
	m_move = false;

	pHousing->Init();
}
